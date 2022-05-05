#include "EndDevice.h"
#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <TimeLib.h>

/**************************************************************************************************************************/
/*LoRa Mode Para*/
#define RF_FREQUENCY 470000000  // Hz
#define TX_OUTPUT_POWER 10      // dBm 22+-1dbm
#define LORA_BANDWIDTH 0        // [0: 125 kHz,1: 250 kHz,2: 500 kHz,3: Reserved]
#define LORA_SPREADING_FACTOR 7 // [SF7..SF12] 10kb/s-0.5kb/s
#define LORA_CODINGRATE 1       // [1: 4/5,2: 4/6,3: 4/7,4: 4/8]
#define LORA_PREAMBLE_LENGTH 8  // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT 0   // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false
#define RX_TIMEOUT_VALUE 1000
//#define BUFFER_SIZE 51 // Define the payload size here.  { 51, 51, 51, 115, 222, 222 };

#define INSTRUCTION_NETWORKING 1
#define INSTRUCTION_NETWORKED_CONFIRM 2
#define INSTRUCTION_UPLOADING 3
#define INSTRUCTION_UPLOADED_CONFIRM 4



/**************************************************************************************************************************/
static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};
const uint8_t VALIDDATAPOS = 13;
#define LEAP_YEAR(Y)     ( ((Y)>0) && !((Y)%4) && ( ((Y)%100) || !((Y)%400) ) )
EndDeviceInfo_t ThisDeviceInfo;
EndDeviceRoutingInfo_t ThisDeviceRoutingInfo;
EndDeviceTransmitData_t ThisDeciveTransmitData;

uint8_t ifSleepMode;
TimerEvent_t wakeUp;
uint8_t validDataPos = VALIDDATAPOS;

static RadioEvents_t RadioEvents;
uint8_t lorawanModeTryNum = 2;
// extern uint8_t RadioIrqNum;
// extern uint8_t RadioIrqTemp;
uint8_t LoRaWANModeFlag = 0;
//uint8_t EndDeviceID = 1;
uint16_t batteryVoltage = 0;
uint8_t startTime[6];
uint16_t setCycle;
uint8_t networkedFlag = 0;
uint8_t networkingBroadcastnum = 5;  //nomally 10
uint8_t respondAckNum = 3;
uint8_t onTxDone = 0;
uint8_t ifTimeNotInit1 = 1;
uint8_t ifTimeNotInit2 = 1;
uint8_t ifTimeNotInit3 = 1;
bool ifNomalTransmitSuccess = 0;
bool renetworkFlag = 0;
uint8_t monitorData[DEVICEMONITORVALUELENGTH];
uint8_t frameCheck = 0;


void EndDeviceInit(uint8_t EndDeviceID, uint8_t EndDeviceRank, uint8_t EndDeviceBattery)
{
    ThisDeviceInfo.EndDeviceID = EndDeviceID;
    ThisDeviceInfo.EndDeviceRank = EndDeviceRank;
    ThisDeviceInfo.EndDevicePriority = 0;
    ThisDeviceInfo.EndDeviceBattery = EndDeviceBattery;
}

void LoraRandomSend(uint8_t networkingBroadcastnum, uint8_t INSTRUCTION, uint8_t destinationID){
  Serial.println("LoraRandomSend start!");
  IfDeviceReceivedParaInit();
  uint16_t randomTimeSum = 0;
  uint8_t num = networkingBroadcastnum;
  while(num){
    PreparePacket(INSTRUCTION, destinationID);
    Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE );
    uint16_t rt = random(100, 1000);
    delay(rt);
    randomTimeSum += rt;
    num--;
  }
  SetLowPowerTimer((uint32_t)(1000*networkingBroadcastnum - randomTimeSum));
}

void LoraRandomNormalSend(uint8_t rankIntervalNum, uint8_t INSTRUCTION, uint8_t destinationID){
  Serial.println("LoraRandomNormalSend start!");
  IfDeviceReceivedParaInit();
  uint8_t num = rankIntervalNum;
  while(!ifNomalTransmitSuccess && num){
    delay(random(0, 400));
    PreparePacket(INSTRUCTION, destinationID);
    Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE );
    delay(200);
    OpenRadioDuration(400);
    num--;
  }
}

void PreparePacket(uint8_t insturction, uint8_t destinationDeviceID){
  txPacket[0] = insturction;
  txPacket[1] = hour();
  txPacket[2] = minute();
  txPacket[3] = second();
  txPacket[4] = day();
  txPacket[5] = month();
  txPacket[6] = year() - 2000;
  txPacket[7] = ThisDeviceInfo.EndDeviceID;
  txPacket[8] = ThisDeviceInfo.EndDeviceRank;
  txPacket[9] = ThisDeviceInfo.EndDevicePriority;
  txPacket[10] = ReadBattery();
  txPacket[11] = ThisDeviceRoutingInfo.FatherEndDeviceID;
  txPacket[12] = destinationDeviceID;

  //test data
  //txPacket[13] = ENDDEVICEID;
  // for(uint8_t i = 0; i < 12; ++i) Serial.printf("%d ", txPacket[i]);
  // Serial.println();
}

void SetLowPowerTimer(uint32_t sleeptime){
  ifSleepMode = 1;
  TimerSetValue( &wakeUp, sleeptime );
  TimerStart( &wakeUp );
  Serial.printf("Now sleep:%ds. ", sleeptime/1000);
  delay(10);
  Serial.println();
  while(ifSleepMode){
    lowPowerHandler();
  }
}

void WakeUpDevice(){
  ifSleepMode = 0;
}

uint8_t UpdateStartTime(uint8_t  *startTime, uint16_t setCycle){
    startTime[1] += setCycle;
    if(startTime[1] >=60){
      startTime[1] -= 60;
      startTime[0] += 1;
    }
    if(startTime[0] >=24){
      startTime[0] -= 24;
      startTime[3] += 1;
    }
    uint8_t day;
    if(startTime[4] == 2){
      day = LEAP_YEAR(startTime[5]) ? 29 : 28;
    }
    else day = monthDays[startTime[4] - 1];
    if(startTime[3] > day){
      startTime[3] -= day;
      startTime[4]++;
    }
    if(startTime[4] > 12){
      startTime[4]-=12;
      startTime[5]++;
    }
    Serial.print("Network will start at: ");
    for(int i = 0; i < 6; i++){
      Serial.print(startTime[i]);
      Serial.print(" ");
    }
    Serial.println();
}

void DeleteFrontData(){
  if(validDataPos + DEVICEMONITORVALUELENGTH > BUFFER_SIZE){
    uint8_t temp = VALIDDATAPOS;
    for(; temp < validDataPos - DEVICEMONITORVALUELENGTH; ++temp){
      txPacket[temp] = txPacket[temp + DEVICEMONITORVALUELENGTH];
    }
    validDataPos = temp;
  }
}

void ReadMonitorData(uint8_t readType){
  if(readType == 0){
    DeleteFrontData();
    uint8_t data[DEVICEMONITORVALUELENGTH];
    data[0] = ThisDeviceInfo.EndDeviceID;
    data[1] = frameCheck++;
    data[2] = ThisDeviceRoutingInfo.FatherEndDeviceID;
    for( uint8_t i = 3; i < DEVICEMONITORVALUELENGTH; ++i){
      data[i] = i;
    }
    for(uint8_t i = 0; i < DEVICEMONITORVALUELENGTH; ++i){
      txPacket[validDataPos + i] = 1;
    }
    validDataPos += DEVICEMONITORVALUELENGTH;
  }

  else if(readType == 1){
    uint8_t rxStartPos = VALIDDATAPOS;
    while(rxpacket[rxStartPos] != 255){
      DeleteFrontData();
      for(uint8_t i = 0; i < DEVICEMONITORVALUELENGTH; ++i){
        txPacket[validDataPos++] = rxpacket[rxStartPos++];
      }
    }
  } 
}

void UpdateMonitorDataPos(){
  if(ifNomalTransmitSuccess){
    validDataPos = VALIDDATAPOS;
    MonitorDataInit();
    ifNomalTransmitSuccess = 0;
  }
  // else validDataPos += 2;
  // if(validDataPos == BUFFER_SIZE - 1) validDataPos-=2;
}


void OnTxDone(){
  onTxDone = 1;
}


void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  Serial.print(" ");
  Serial.print(minute());
  Serial.print(" ");
  Serial.print(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

//AT+setime=11040203032022;AT+startTime=11040203032022;setCycle:min
//All time format: 11:04:03 3 3 2022

bool checkUserAt(char *cmd, char *content)
{
  char temp[2];
  char temp2[4];
  char temp3[1];
  if (!strcmp(cmd, "setTime"))
  {
    setTime(atoi(strncpy(temp, content, 2)), atoi(strncpy(temp, content + 2, 2)), atoi(strncpy(temp, content + 4, 2)), atoi(strncpy(temp, content + 6, 2)),
            atoi(strncpy(temp, content + 8, 2)), atoi(strncpy(temp2, content + 10, 4)));
    ifTimeNotInit1 = 0;
    return true;
  }
  if(!strcmp(cmd, "startTime")){
    for(int i = 0; i < 5; i++){
      startTime[i] = atoi(strncpy(temp, content + i*2, 2));
    }
    startTime[5] = atoi(strncpy(temp, content + 12, 2));
    // Serial.print("StartTime set success! Network will start at: ");
    // for(int i = 0; i < 6; i++){
    //   Serial.print(startTime[i]);
    //   Serial.print(" ");
    // }
    // Serial.println("");
    ifTimeNotInit2 = 0;
    return true;
  }
  if(!strcmp(cmd, "setCycle")){
    setCycle = atoi(strncpy(temp, content, 2));
    ifTimeNotInit3 = 0;
    return true;
  }
  if(!strcmp(cmd, "status")){
    Serial.print("Now time is: ");
    Serial.printf("%d:%d:%d, %d:%d:%d", hour(), minute(), second(), day(), month(), year());
    Serial.println();
    Serial.print("Network will start at: ");
    for(int i = 0; i < 6; i++){
      Serial.print(startTime[i]);
      Serial.print(" ");
    }
    Serial.println();
    Serial.printf("ID is %d. ", ThisDeviceInfo.EndDeviceID);Serial.println();
    return true;
  }
  if(!strcmp(cmd, "PrimaryParaInit")){
    uint8_t select = atoi(strncpy(temp3, content, 1));
    uint8_t id = atoi(strncpy(temp3, content + 1, 1));
    PrimaryParaInit(nwkSKey, appSKey, devAddr, ENDDEVICEID, select, id);
    return true;
  }
  return false;
}

void RadioIrqParaInit()
{
  RadioIrqNum = 0;
  RadioIrqTemp = 0;
  onTxDone = 0;
}
void LoRaPhyInit()
{
  RadioEvents.RxDone = OnRxDone;
  RadioEvents.TxDone = OnTxDone;

  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);
  Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                    LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                    LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                    true, 0, 0, LORA_IQ_INVERSION_ON, 3000);
}

void LoRaWANPhyInit(){
  LoRaWAN.init(LORAWAN_CLASS, ACTIVE_REGION);
  LoRaWAN.join(); //abp
  loRaWANReceiveFlag = 0;
}

uint8_t ReadBattery(){
  uint8_t batteryVoltage;
  pinMode(VBAT_ADC_CTL,OUTPUT);
  digitalWrite(VBAT_ADC_CTL,LOW);
  batteryVoltage = analogRead(ADC)*2 / 100;
  pinMode(VBAT_ADC_CTL, INPUT);
  return batteryVoltage;
}

void WAMPLInfoInit(){
  EndDeviceInit(ENDDEVICEID, 0, ReadBattery());
  ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum = 0;
  ThisDeviceRoutingInfo.SonEndDeviceNum = 0;
  MonitorDataInit();
}



void SelectFatherEndDevice(){
  Serial.println("SelectFatherEndDevice Start!");
  uint8_t neiborNum = ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum;
  if(neiborNum == 0) return;
  uint8_t weight[neiborNum];
  for(uint8_t i = 0; i< neiborNum; ++i){
    weight[i] = (50*ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[i].FatherEndDeviceBattery/70 + \
    30*(ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[i].FatherEndDeviceRSSI+174)/165 + \
    20*(ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[i].FatherEndDeviceSNR+15)/27);
    Serial.printf("Calculate weight... Potential father ID is %d, weight is %d. ", ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[i].FatherEndDeviceID, weight[i]);
    }
  uint8_t maxWeight = weight[0];
  uint8_t pos = 0;
  for(uint8_t i = 1; i< neiborNum; ++i){
    if(weight[i] > maxWeight){
      maxWeight = weight[i];
      pos = i;
    } 
  }
  Serial.printf("neibornum:%d, maxweightpos: %d %d", neiborNum, pos, weight[pos]);
  ThisDeviceRoutingInfo.FatherEndDeviceID = ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[pos].FatherEndDeviceID;
  ThisDeviceInfo.EndDeviceRank = ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[pos].FatherEndDeviceRank + 1;
  networkedFlag = 1;
}





uint32_t CalcAllDeviceStartTime(){
  //49 day
  return ((startTime[3] - day()) * 86400 + (startTime[0] - hour())*3600 + (startTime[1] - minute()) * 60 + startTime[2] - second()) * 1000; //milisecond from day hour min sec
}

void OpenRadioDuration(uint32_t duration){
  Serial.println("OpenRadioDuration start!");
  IfDeviceReceivedParaInit();
  for(uint16_t i = 0; i < duration / 100; i++){
      Radio.Rx( 0 );
      //Radio.IrqProcess( );
      delay(100);  //has to be 500
    }
  // Radio.Rx( 0 );
  // delay(duration);
  Radio.Sleep();
  Serial.println("OpenRadioDuration finish!");
}

void MonitorDataInit(){
  for(uint8_t i = VALIDDATAPOS; i < BUFFER_SIZE; i++) txPacket[i] = 255;
}

void IfDeviceReceivedParaInit(){
  for(uint8_t i = 0; i < 20; i++) ThisDeviceRoutingInfo.IfDeviceReceived[i] = 0;
}

void RoutingInfoInit(){
  ThisDeviceRoutingInfo.FatherEndDeviceID = 0;
  IfDeviceReceivedParaInit();
  ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum = 0;
  ThisDeviceRoutingInfo.SonEndDeviceNum = 0;
}

void UpdateTime(uint8_t* rxpacket){
  Serial.print("Before Update: ");
  digitalClockDisplay();
  setTime(rxpacket[1], rxpacket[2], rxpacket[3], rxpacket[4], rxpacket[5], 2000 + rxpacket[6]);
  Serial.print("After Update: ");
  digitalClockDisplay();
}

void ArrayCopy(uint8_t* array1, uint8_t* array2, uint8_t size){
  for(uint8_t i = 0; i < size; ++i){
    array1[i] = array2[i];
  }
}
void PrimaryParaInit(uint8_t* nwkSKey, uint8_t* appSKey, uint32_t& devAddr, uint8_t& ENDDEVICEID, uint8_t select, uint8_t id){
  ENDDEVICEID = id;
  if(select == 1){
    uint8_t nwkSKey_p[16] = {0x8D, 0x47, 0x77, 0x25, 0x91, 0x1B, 0xBE, 0x88, 0x38, 0x81, 0x26, 0x7A, 0x51, 0x15, 0xD3, 0x75};
    uint8_t appSKey_p[16] = {0x55, 0x78, 0x2A, 0x3B, 0xE9, 0x6D, 0x2C, 0x31, 0x44, 0xDF, 0xB8, 0x36, 0xE9, 0x8D, 0x9A, 0xEC};
    ArrayCopy(nwkSKey, nwkSKey_p,16); ArrayCopy(appSKey, appSKey_p,16);
    devAddr = (uint32_t)0x260BFFCF;
  }
  else if(select == 2){
    uint8_t nwkSKey_p[16] = {0x84, 0xAB, 0xDE, 0xB9, 0xD8, 0xBF, 0xB9, 0x9C, 0x8C, 0x61, 0x85, 0xA0, 0x2E, 0xAF, 0x2D, 0x4D};
    uint8_t appSKey_p[16] = {0x68, 0x29, 0xFB, 0x5B, 0xB5, 0x36, 0xF0, 0xE1, 0x7B, 0x92, 0xC3, 0xA8, 0x10, 0x46, 0x5E, 0x9A};
    ArrayCopy(nwkSKey, nwkSKey_p,16); ArrayCopy(appSKey, appSKey_p,16);
    devAddr = (uint32_t)0x260B7982;
  }
}

void LoRaSend(uint8_t* txdata){
  char txstr[BUFFER_SIZE];
  for(uint8_t i = 0; i < BUFFER_SIZE; ++i){
    sprintf(txstr + strlen(txstr),"%d", txdata[i]);
  }
  Radio.Send( (uint8_t *)txstr, BUFFER_SIZE );
  delay(10);
}

void LoRaReceive(uint8_t* payload, uint8_t* rxdata){

}