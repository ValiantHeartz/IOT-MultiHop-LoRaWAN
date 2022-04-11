# 1 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
# 2 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
//#include "LoRaWanMinimal_APP.h"
# 4 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
# 5 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
# 6 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
# 7 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2

/**************************************************************************************************************************/
// /*LoRa Mode Para*/
// #define RF_FREQUENCY 915000000  // Hz
// #define TX_OUTPUT_POWER 14      // dBm 22+-1dbm
// #define LORA_BANDWIDTH 0        // [0: 125 kHz,1: 250 kHz,2: 500 kHz,3: Reserved]
// #define LORA_SPREADING_FACTOR 7 // [SF7..SF12] 10kb/s-0.5kb/s
// #define LORA_CODINGRATE 1       // [1: 4/5,2: 4/6,3: 4/7,4: 4/8]
// #define LORA_PREAMBLE_LENGTH 8  // Same for Tx and Rx
// #define LORA_SYMBOL_TIMEOUT 0   // Symbols
// #define LORA_FIX_LENGTH_PAYLOAD_ON false
// #define LORA_IQ_INVERSION_ON false
// #define RX_TIMEOUT_VALUE 1000
// #define BUFFER_SIZE 51 // Define the payload size here.  { 51, 51, 51, 115, 222, 222 };






//#define ENDDEVICEID 3
uint8_t ENDDEVICEID = 1;
uint16_t rankIntervalTime = 5000;
//static const uint16_t normalTransmitTime = 4000
/**************************************************************************************************************************/
/*LoRaWAN Mode Para*/
/* OTAA para*/
uint8_t devEui[] = {0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x04, 0xEF, 0xB9};
uint8_t appEui[] = {0x81, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x01};
uint8_t appKey[] = {0xD9, 0x0A, 0x1C, 0xD7, 0xE0, 0x88, 0x9A, 0x4C, 0x54, 0xEA, 0x4B, 0x56, 0x40, 0x47, 0x37, 0xBB};

/* ABP para:3B*/ //c1-c2
// uint8_t nwkSKey[] = {0xC1, 0x39, 0xFB, 0x90, 0x25, 0x3A, 0xD0, 0xD3, 0xD9, 0x00, 0x1E, 0x28, 0xFD, 0xF9, 0x47, 0x52};
// uint8_t appSKey[] = {0x61, 0x8B, 0x3F, 0x9E, 0x0E, 0x97, 0x3B, 0x97, 0x93, 0x5E, 0x39, 0x96, 0x9A, 0x0E, 0xF3, 0x20};
// uint32_t devAddr = (uint32_t)0x2800F603;

/* ABP para:3a*/ //37-38
// uint8_t nwkSKey[] = {0x37, 0x0B, 0xF7, 0x30, 0xB3, 0xE5, 0x70, 0xB7, 0x80, 0xC6, 0x8F, 0x44, 0xAA, 0xF8, 0xB5, 0x00};
// uint8_t appSKey[] = {0x1A, 0xFE, 0xBB, 0x36, 0xF6, 0x4F, 0xB2, 0xD1, 0x04, 0xEF, 0x77, 0x13, 0x77, 0xB8, 0x5B, 0x5F};
// uint32_t devAddr = (uint32_t)0x2800F602;

/*abp ttn*/
uint8_t nwkSKey[] = {0x8D, 0x47, 0x77, 0x25, 0x91, 0x1B, 0xBE, 0x88, 0x38, 0x81, 0x26, 0x7A, 0x51, 0x15, 0xD3, 0x75};
uint8_t appSKey[] = {0x55, 0x78, 0x2A, 0x3B, 0xE9, 0x6D, 0x2C, 0x31, 0x44, 0xDF, 0xB8, 0x36, 0xE9, 0x8D, 0x9A, 0xEC};
uint32_t devAddr = (uint32_t)0x260BFFCF;

/*LoraWan channelsmask, default channels 0-7*/
uint16_t userChannelsMask[6] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/*LoraWan region, select in arduino IDE tools*/
LoRaMacRegion_t loraWanRegion = LORAMAC_REGION_CN470;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t loraWanClass = CLASS_A;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 15000;

/*OTAA or ABP*/

# 66 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 66 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    overTheAirActivation = 
# 66 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                           false
# 66 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                          ;

/*ADR enable*/

# 69 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 69 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    loraWanAdr = 
# 69 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                 true
# 69 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                            ;

/* set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again */

# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    keepNet = 
# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
              false
# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                 ;

/* Indicates if the node is sending confirmed or unconfirmed messages */

# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    isTxConfirmed = 
# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                    true
# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                      ;

/* Application port */
uint8_t appPort = 2;

/**************************************************************************************************************************/
/*This File Variables*/
uint8_t confirmedNbTrials = 4; //lorawan 1.0.2-18.4
uint8_t txPacket[51] = {1,2,3};
uint8_t rxpacket[51];
int16_t rssi = 0, rxSize = 0, snr = 0;
extern SH1107Wire display;

/**************************************************************************************************************************/
/*Functions*/
// void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
// void digitalClockDisplay();
// bool checkUserAt(char *cmd, char *content);
// static void prepareTxFrame(uint8_t port);
// void RadioIrqParaInit();
// void LoRaPhyInit();
// void LoRaWANPhyInit();
// uint8_t ReadBattery();
// void WAMPLInfoInit();
// //void PreparePacket(uint8_t insturction);
// void SelectFatherEndDevice();
// //void SetLowPowerTimer(uint32_t sleeptime);
// //void WakeUpDevice();
// uint32_t CalcAllDeviceStartTime();
// void OpenRadioDuration(uint16_t duration);
// //void LoraRandomSend(uint8_t networkingBroadcastnum, uint8_t INSTRUCTION, uint8_t destinationID);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

/**************************************************************************************************************************/
/*Main Function*/
void setup()
{
  Serial.begin(115200);



  /*Wait for Time Init*/
  while(ifTimeNotInit1||ifTimeNotInit2||ifTimeNotInit3) lowPowerHandler();
  Serial.println("Time init success!");
  /*LoRaWAN Mode Init*/
  TimerInit( &wakeUp, WakeUpDevice );
  SetLowPowerTimer(CalcAllDeviceStartTime());
  WAMPLInfoInit();
  LoRaWANPhyInit();
  Serial.println(ThisDeviceInfo.EndDeviceID);
  Serial.println();
  while (lorawanModeTryNum--)
  {
    LoRaWAN.sendrequestconfirm(51, txPacket, 1, 1);
    Serial.println("lorawan send");
    delay(1000);
  }
  if (RadioIrqNum == 2)
  {
    LoRaWANModeFlag = 1;
    Serial.println("LoRaWAN Init Success!");
    ThisDeviceInfo.EndDeviceRank = 1;
  }

  /*LoRa Phy Init*/
  else
  {
    LoRaWANModeFlag = 0;
    LoRaPhyInit();
    Serial.println("LoRa Init Success!");
  }
  UpdateStartTime(startTime, setCycle);
  SetLowPowerTimer(CalcAllDeviceStartTime());
}

void loop()
{
  delay(10);
  Serial.println("now all start");
  digitalClockDisplay();
  if(!networkedFlag){
    if(LoRaWANModeFlag){
      Serial.println("Lorawan mode, sending networking signal.");
      LoRaPhyInit();
      LoraRandomSend(networkingBroadcastnum, 1, 0); //0 for broadcast 
      OpenRadioDuration(1000*respondAckNum);
      networkedFlag = 1;
      Serial.println("Lorawan networking success.");
    }
    else{
      OpenRadioDuration(1000*networkingBroadcastnum);
      SelectFatherEndDevice();
      if(networkedFlag){
        LoraRandomSend(networkingBroadcastnum, 2, ThisDeviceRoutingInfo.FatherEndDeviceID);
        OpenRadioDuration(1000*respondAckNum);
      }
    }
  }
  if(networkedFlag){
    Serial.printf("Networked, Father device id is: %d. Son device id is: %d. Device rank is: %d", ThisDeviceRoutingInfo.FatherEndDeviceID,
    ThisDeviceRoutingInfo.SonEndDeviceID[ThisDeviceRoutingInfo.SonEndDeviceNum - 1], ThisDeviceInfo.EndDeviceRank);
    Serial.println();

    UpdateStartTime(startTime, setCycle);
    rounds++;
    Serial.printf("sleep:%d",CalcAllDeviceStartTime());
    uint16_t thisDeviceRankTillStartReceiveTime = CalcAllDeviceStartTime() - ThisDeviceInfo.EndDeviceRank * rankIntervalTime;
    SetLowPowerTimer(thisDeviceRankTillStartReceiveTime);
    //SetLowPowerTimer(1000);  //for test
    if(LoRaWANModeFlag)
    {
      LoRaPhyInit();
      OpenRadioDuration(rankIntervalTime);
      LoRaWANPhyInit();
      RadioIrqParaInit();
      Serial.println("lorawan sending");
      for(uint8_t i = 0; i < 51; i++) Serial.printf("%d ", txPacket[i]);
      Serial.println();
      ifNomalTransmitSuccess = 0;
      ReadMonitorData(txPacket);
      PreparePacket(3, 0);
      for(uint8_t i = 0; i < 51; i++) Serial.printf("%d ", txPacket[i]);
      Serial.println();
      LoRaWAN.sendrequestconfirm(51, txPacket, 1, 1); //此处可优化，根据是否收到网关回复决定是否重发
      LoRaWAN.sendrequestconfirm(51, txPacket, 1, 1);
      if (RadioIrqNum == 2) ifNomalTransmitSuccess = 1;
      UpdateMonitorDataPos(ifNomalTransmitSuccess);
    }
    else{
      if(ThisDeviceRoutingInfo.SonEndDeviceNum == 0){
        SetLowPowerTimer(rankIntervalTime);
      }
      else{
        OpenRadioDuration(rankIntervalTime);
      }
      ifNomalTransmitSuccess = 0;
      ReadMonitorData(txPacket);
      //PreparePacket(INSTRUCTION_UPLOADING, ThisDeviceRoutingInfo.FatherEndDeviceID);
      Serial.println("lora sending");
      for(uint8_t i = 0; i < 51; i++) Serial.printf("%d ", txPacket[i]);
      Serial.println();
      LoraRandomNormalSend(rankIntervalTime/1000, 3, ThisDeviceRoutingInfo.FatherEndDeviceID); //所有下级节点发送5秒
      UpdateMonitorDataPos(ifNomalTransmitSuccess);
    }
  }

  if(rounds == 100){
    networkedFlag = 0;
    RoutingInfoInit();
  }

  void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  uint8_t pktHeaderLen = 0;
  LoRaMacHeader_t macHdr;
  macHdr.Value = payload[pktHeaderLen++];
  switch (macHdr.Bits.MType)
  {
  case FRAME_TYPE_DATA_UNCONFIRMED_DOWN:
  {
    Serial.printf("receive downlink success!");
  }
  }

  rssi = rssi;
  rxSize = size;
  memcpy(rxpacket, payload, size);
  rxpacket[size] = '\0';
  turnOnRGB(0x005000 /*color green, light 0x10*/, 0);
  Radio.Sleep();
  uint8_t rxInstruction = rxpacket[0];
  uint8_t sourceDeviceID = rxpacket[7];
  uint8_t destinationDevice = rxpacket[12];
  for(uint8_t i = 0; i < size; i++){
      Serial.printf("%d,", rxpacket[i]);
    }

  if(rxInstruction == 1){
    Serial.println("INSTRUCTION_NETWORKING signal receive success!");
    if(!networkedFlag && !ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID]){
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceID = rxpacket[7];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceRank = rxpacket[8];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDevicePriority = rxpacket[9];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceBattery = rxpacket[10];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceRSSI = rssi;
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceSNR = snr;
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum++;
      ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID] = 1;
    }
    UpdateTime(txPacket);
  }
  if(rxInstruction == 2 && destinationDevice == ThisDeviceInfo.EndDeviceID && !ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID]){
    ThisDeviceRoutingInfo.SonEndDeviceID[ThisDeviceRoutingInfo.SonEndDeviceNum] = rxpacket[7];
    ThisDeviceRoutingInfo.SonEndDeviceNum++;
    ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID] = 1;
  }
  if(rxInstruction == 3 && destinationDevice == ThisDeviceInfo.EndDeviceID && !ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID]){
    ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID] = 1;
    //while(txPacket[txStartPos]!=255) txStartPos++;
    uint8_t rxStartPos = VALIDDATAPOS;
    while(rxpacket[rxStartPos] != 255){
      txPacket[validDataPos] = rxpacket[rxStartPos];
      validDataPos++; rxStartPos++;
      if(validDataPos == 51) break;
    }
    PreparePacket(4, sourceDeviceID);
    Radio.Send( (uint8_t *)txPacket, 51 );
    delay(100);
    Radio.Send( (uint8_t *)txPacket, 51 );
    delay(100);
    ThisDeviceRoutingInfo.FatherEndDeviceID = 0;
  }
  if(rxInstruction == 4 && destinationDevice == ThisDeviceInfo.EndDeviceID){
    ifNomalTransmitSuccess = 1;
    UpdateTime(txPacket);
  }
  //Serial.printf("\r\nreceive packet \"%s\" with rssi %d , length %d\r\n", rxpacket, rssi, rxSize);
  Serial.printf("LoRa message received, instruction: %d, source ID: %d", rxInstruction, sourceDeviceID);
  Serial.println();
}
