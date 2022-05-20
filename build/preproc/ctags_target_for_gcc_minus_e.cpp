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

uint16_t rankIntervalTime = 20000;
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

/*abp ttn*/// 8D->7D
uint8_t nwkSKey[16] = {0x7D, 0x47, 0x77, 0x25, 0x91, 0x1B, 0xBE, 0x88, 0x38, 0x81, 0x26, 0x7A, 0x51, 0x15, 0xD3, 0x75};
uint8_t appSKey[16] = {0x55, 0x78, 0x2A, 0x3B, 0xE9, 0x6D, 0x2C, 0x31, 0x44, 0xDF, 0xB8, 0x36, 0xE9, 0x8D, 0x9A, 0xEC};
uint32_t devAddr = (uint32_t)0x260BFFCF;
//84>74
// uint8_t nwkSKey[] = {0x84, 0xAB, 0xDE, 0xB9, 0xD8, 0xBF, 0xB9, 0x9C, 0x8C, 0x61, 0x85, 0xA0, 0x2E, 0xAF, 0x2D, 0x4D};
// uint8_t appSKey[] = {0x68, 0x29, 0xFB, 0x5B, 0xB5, 0x36, 0xF0, 0xE1, 0x7B, 0x92, 0xC3, 0xA8, 0x10, 0x46, 0x5E, 0x9A};
// uint32_t devAddr = (uint32_t)0x260B7982;


/*LoraWan channelsmask, default channels 0-7*/
uint16_t userChannelsMask[6] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/*LoraWan region, select in arduino IDE tools*/
LoRaMacRegion_t loraWanRegion = LORAMAC_REGION_CN470;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t loraWanClass = CLASS_A;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 15000;

/*OTAA or ABP*/

# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    overTheAirActivation = 
# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                           false
# 72 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                          ;

/*ADR enable*/

# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    loraWanAdr = 
# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                 true
# 75 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                            ;

/* set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again */

# 78 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 78 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    keepNet = 
# 78 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
              false
# 78 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                 ;

/* Indicates if the node is sending confirmed or unconfirmed messages */

# 81 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 81 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    isTxConfirmed = 
# 81 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                    true
# 81 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                      ;

/* Application port */
uint8_t appPort = 2;

/**************************************************************************************************************************/
/*This File Variables*/
uint8_t confirmedNbTrials = 4; //lorawan 1.0.2-18.4
uint8_t txPacket[115 /*51,115,222*/] = {1,2,3};
uint8_t rxpacket[115 /*51,115,222*/];
uint8_t loRaLWJudgeFlag = 0;
uint8_t rounds = 0;
uint8_t nextNetworkingPeriod = 10;

uint8_t tempEndDeviceNum = 0;

/**************************************************************************************************************************/
/*Functions*/
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
  for(uint8_t i = 0; i < 115 /*51,115,222*/; ++i) rxpacket[i] = 255;
  for(uint8_t i = 0; i < 115 /*51,115,222*/; ++i) txPacket[i] = 255;
}

void loop()
{
  Serial.printf("Start running... This device ID is %d, priority is %d.", ThisDeviceInfo.EndDeviceID, ThisDeviceInfo.EndDevicePriority);
  Serial.println();
  /*LW or lora judge*/
  if(!loRaLWJudgeFlag){
    digitalClockDisplay();
    LoRaWANPhyInit();
    uint8_t temp = lorawanModeTryNum;
    while (temp--)
    {
      LoRaWAN.sendrequestconfirm(115 /*51,115,222*/, txPacket, 1, 1);
      delay(1000);
    }
    if (loRaWANReceiveFlag)
    {
      LoRaWANModeFlag = 1;
      Serial.println("LoRaWAN Init Success!");
      ThisDeviceInfo.EndDeviceRank = 1;
      loRaWANReceiveFlag = 0;
    }
    /*LoRa Phy Init*/
    else
    {
      LoRaWANModeFlag = 0;
      LoRaPhyInit();
      Serial.println("LoRa Init Success!");
    }
    loRaLWJudgeFlag = 1;
    UpdateStartTime(startTime, setCycle);
    SetLowPowerTimer(CalcAllDeviceStartTime());
  }

  /*networking*/
  if(!networkedFlag){
    digitalClockDisplay();
    Serial.printf("Networking... This device ID is %d", ThisDeviceInfo.EndDeviceID);
    Serial.println();
    if(LoRaWANModeFlag){
      Serial.println("Lorawan mode, sending networking signal.");
      LoRaPhyInit();
      LoraRandomSend(networkingBroadcastnum, 1, 0); //0 for broadcast 
      AssignPriority(3);
      networkedFlag = 1;
      Serial.println("Lorawan networking success.");
    }
    else{
      OpenRadioDuration(1000*5);
      SelectFatherEndDevice();
      if(networkedFlag){
        ReceivePriority(3);
        LoraRandomSend(networkingBroadcastnum, 1, 0);
        Serial.println("Lora networking...");
        AssignPriority(3);
      }
      else SetLowPowerTimer(5000*3);
    }
    if(rounds == nextNetworkingPeriod - 3){ //最多6级节点
      UpdateStartTime(startTime, setCycle*(nextNetworkingPeriod - 2));
      loRaLWJudgeFlag = 0;
      uint32_t thisDeviceRankTillStartReceiveTime = CalcAllDeviceStartTime();
      SetLowPowerTimer(thisDeviceRankTillStartReceiveTime);
    }
  }

  /*Nomally transmit*/

  if(networkedFlag){
    Serial.printf("Nomally transmitting... This device ID is %d. ", ThisDeviceInfo.EndDeviceID);
    Serial.println();
    Serial.printf("Father device id is: %d. Son device num is: %d. Device rank is: %d. Rounds is %d. Priority is %d. ", ThisDeviceRoutingInfo.FatherEndDeviceID,
    ThisDeviceRoutingInfo.SonEndDeviceNum, ThisDeviceInfo.EndDeviceRank, rounds, ThisDeviceInfo.EndDevicePriority);
    for(uint8_t i = 0; i < ThisDeviceRoutingInfo.SonEndDeviceNum; ++i){
      Serial.printf("Son device %d is %d. ", i+1, ThisDeviceRoutingInfo.SonEndDeviceID[i]);
    }

    //sleep
    UpdateStartTime(startTime, setCycle);
    uint32_t thisDeviceRankTillStartReceiveTime = CalcAllDeviceStartTime() - ThisDeviceInfo.EndDeviceRank * rankIntervalTime;
    SetLowPowerTimer(thisDeviceRankTillStartReceiveTime);
    digitalClockDisplay();

    if(LoRaWANModeFlag)
    {
      LoRaPhyInit();
      OpenRadioDuration(rankIntervalTime);
      LoRaWANPhyInit();
      //RadioIrqParaInit();
      Serial.println("lorawan sending");
      ReadMonitorData(0);
      PreparePacket(3, 0);
      for(uint8_t i = 0; i < 115 /*51,115,222*/; i++) Serial.printf("%d ", txPacket[i]);
      Serial.println();
      LoRaWAN.sendrequestconfirm(115 /*51,115,222*/, txPacket, 1, 1);
      if(loRaWANReceiveFlag) ifNomalTransmitSuccess = 1;
      UpdateMonitorDataPos();
    }
    else{
      LoRaPhyInit();
      if(ThisDeviceRoutingInfo.SonEndDeviceNum == 0){
        SetLowPowerTimer((uint32_t)rankIntervalTime);
      }
      else{
        OpenRadioDuration((uint32_t)rankIntervalTime);
      }
      ReadMonitorData(0);
      PreparePacket(3, ThisDeviceRoutingInfo.FatherEndDeviceID);
      Serial.println("lora sending");
      for(uint8_t i = 0; i < 115 /*51,115,222*/; i++) Serial.printf("%d ", txPacket[i]);
      Serial.println();
      LoraTDMATransmit();
      UpdateMonitorDataPos();
    }
  }

  rounds++;

  if(rounds == (nextNetworkingPeriod - 2)){
    networkedFlag = 0;
    loRaLWJudgeFlag = 0;
    RoutingInfoInit();
    rounds = 0;
    UpdateStartTime(startTime, setCycle);
    Serial.print("Wait for next cycle... Time left: ");
    Serial.println(CalcAllDeviceStartTime()/1000);
    SetLowPowerTimer(CalcAllDeviceStartTime());
  }
}

  void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  // uint8_t pktHeaderLen = 0;
  // LoRaMacHeader_t macHdr;
  // macHdr.Value = payload[pktHeaderLen++];
  // switch (macHdr.Bits.MType)
  // {
  //   case FRAME_TYPE_DATA_UNCONFIRMED_DOWN:
  //   {
  //     Serial.printf("receive downlink success!");
  //   }
  // }
  rxsnr = snr;
  rxrssi = rssi;
  rxsize = size;
  for(uint8_t i = 0; i < rxsize; ++i){
    rxpacket[i] = payload[i];
  }
  //Radio.Sleep();
  uint8_t rxInstruction = rxpacket[0];
  uint8_t sourceDeviceID = rxpacket[7];
  uint8_t destinationDevice = rxpacket[12];
  uint8_t sourceDevicePriority = rxpacket[9];
  if(rxInstruction == 4 && destinationDevice == ThisDeviceInfo.EndDeviceID){
    UpdateTime(rxpacket);
  }
  Serial.println("Signal received!");
  for(uint8_t i = 0; i < rxsize; i++){
      Serial.printf("%d,", rxpacket[i]);
  }
  Serial.println();
  if(rxInstruction == 1){
    if(!networkedFlag && !ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID]){
      Serial.println("INSTRUCTION_NETWORKING signal receive success!");
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceID = rxpacket[7];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceRank = rxpacket[8];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDevicePriority = rxpacket[9];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceBattery = rxpacket[10];
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceRSSI = rxrssi;
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceInfo[ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum].FatherEndDeviceSNR = rxsnr;
      ThisDeviceRoutingInfo.NeiborFatherEndDeviceNum++;
      ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID] = 1;
    }
  }
  if(rxInstruction == 2 && destinationDevice == ThisDeviceInfo.EndDeviceID && sourceDevicePriority == 0){
    uint8_t assignPriority = FindEndDeviceIDAssignedPriority(sourceDeviceID);
    if(assignPriority == ThisDeviceRoutingInfo.SonEndDeviceNum + 1){
      ThisDeviceRoutingInfo.SonEndDeviceID[ThisDeviceRoutingInfo.SonEndDeviceNum] = sourceDeviceID;
      ThisDeviceRoutingInfo.SonEndDeviceNum++;
    }
    PreparePacket(5, sourceDeviceID);
    txPacket[9] = assignPriority;
    Radio.Send( (uint8_t *)txPacket, 115 /*51,115,222*/ );
    delay(210);
    //while(!onTxDone){delay(1);} //200ms
  }
  if(rxInstruction == 3 && destinationDevice == ThisDeviceInfo.EndDeviceID && !ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID]){
    ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID] = 1;
    ReadMonitorData(1);rxrssi = 0; rxsnr = 0;
    PreparePacket(4, sourceDeviceID);
    if(sourceDevicePriority == 0){
      uint8_t assignPriority = FindEndDeviceIDAssignedPriority(sourceDeviceID);
      if(assignPriority == ThisDeviceRoutingInfo.SonEndDeviceNum + 1){
        ThisDeviceRoutingInfo.SonEndDeviceID[ThisDeviceRoutingInfo.SonEndDeviceNum] = sourceDeviceID;
        ThisDeviceRoutingInfo.SonEndDeviceNum++;
      }
      txPacket[9] = assignPriority;
    }
    Radio.Send( (uint8_t *)txPacket, 115 /*51,115,222*/ );
    delay(210);
    Radio.Rx(0);
  }
  if(rxInstruction == 4 && destinationDevice == ThisDeviceInfo.EndDeviceID){
    ifNomalTransmitSuccess = 1;
    if(ThisDeviceInfo.EndDevicePriority == 0){
      ThisDeviceInfo.EndDevicePriority = sourceDevicePriority;
    }
  }
  if(rxInstruction == 5 && destinationDevice == ThisDeviceInfo.EndDeviceID){
    ThisDeviceInfo.EndDevicePriority = rxpacket[9];
  }
}

void OnTxDone(){
  onTxDone = 1;
}
