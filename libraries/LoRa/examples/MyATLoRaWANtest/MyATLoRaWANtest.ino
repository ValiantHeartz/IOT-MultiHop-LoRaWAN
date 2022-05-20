#include "LoRaWan_APP.h"
//#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"
#include <TimeLib.h>
#include <Wire.h>
#include "C:\Users\zhoul\AppData\Local\Arduino15\packages\CubeCell\hardware\CubeCell\1.3.0\libraries\LoRa\src\EndDevice.h"

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

#define INSTRUCTION_NETWORKING 1
#define INSTRUCTION_NETWORKED_CONFIRM 2
#define INSTRUCTION_UPLOADING 3
#define INSTRUCTION_UPLOADED_CONFIRM 4
#define INSTRUCTION_ASSIGN_PRIORITY 5

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
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t loraWanClass = LORAWAN_CLASS;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 15000;

/*OTAA or ABP*/
bool overTheAirActivation = LORAWAN_NETMODE;

/*ADR enable*/
bool loraWanAdr = LORAWAN_ADR;

/* set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again */
bool keepNet = LORAWAN_NET_RESERVE;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = LORAWAN_UPLINKMODE;

/* Application port */
uint8_t appPort = 2;

/**************************************************************************************************************************/
/*This File Variables*/
uint8_t confirmedNbTrials = 4; //lorawan 1.0.2-18.4
uint8_t txPacket[BUFFER_SIZE] = {1,2,3};
uint8_t rxpacket[BUFFER_SIZE];
uint8_t loRaLWJudgeFlag = 0;
uint8_t rounds = 0;
uint8_t nextNetworkingPeriod = 10;

uint8_t tempEndDeviceNum = 0;

/**************************************************************************************************************************/
/*Functions*/
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout();
/**************************************************************************************************************************/
/*Main Function*/
void setup()
{
  Serial.begin(115200);
#if (AT_SUPPORT)
  enableAt();
#endif
  /*Wait for Time Init*/
  // while(ifTimeNotInit1||ifTimeNotInit2||ifTimeNotInit3) lowPowerHandler();
  Serial.println("Time init success!");
  // /*LoRaWAN Mode Init*/
  // TimerInit( &wakeUp, WakeUpDevice );
  // SetLowPowerTimer(CalcAllDeviceStartTime());
  WAMPLInfoInit();
  LoRaPhyInit();
  for(uint8_t i = 0; i < BUFFER_SIZE; ++i) rxpacket[i] = 255;
  for(uint8_t i = 0; i < BUFFER_SIZE; ++i) txPacket[i] = 255;
}

bool rxtx =1;
bool rxflag = 0;
bool txtimeoutflag = 0;
uint32_t time1 = 0;
uint32_t time2 = 0;
uint32_t time3 = 0;
void loop()
{
  // //  pingpong
  //  if(rxtx == 0){
  //   Serial.println("this is tx");
  //   onTxDone = 0;
  //   txtimeoutflag = 0;
  //   PreparePacket(1, 0);
  //   time1 = RtcGetTimerValue();
  //   Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE - 1 );
  //   //Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE - 2);
  //   while(!onTxDone){delay(1);}//lowPowerHandler();}
  //   Serial.println("start rx");
  //   rxflag = 0;
  //   Radio.Rx( 0 );
  //   delay(210);
  //   //while(!rxflag){delay(1);}
  //   // Radio.Sleep();
  //   // uint32_t time2 = RtcGetTimerValue();
  //   // Serial.printf("spend time:%d", time2 - time1);
  //   // Serial.println();
  // }
  // else if(rxtx == 1){
  //   while(1){
  //     Radio.Rx( 0 );
  //     rxflag = 0;
  //     onTxDone = 0;
  //     Serial.println("this is rx");
  //     delay(210);
  //     //while(!rxflag){delay(1);}
  //     //Serial.println("rx success.");
  //     //Radio.Sleep();
  //     PreparePacket(INSTRUCTION_UPLOADED_CONFIRM, 0);
  //     Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE );
  //     while(!onTxDone){delay(1);}
  //   }
  // }
  OpenRadioDuration(9000);
  delay(2000);
  // PreparePacket(1, 0);
  // Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE - 1 );
  // delay(210);
}

  void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  PreparePacket(1, 0);
  Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE );
  delay(210);
  Radio.Rx(0);
  rxflag = 1;
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
  uint8_t rxsnr = snr;
  int16_t rxrssi = rssi;
  uint16_t rxsize = size;
  for(uint8_t i = 0; i < rxsize; ++i){
    rxpacket[i] = payload[i];
  }
  //Radio.Sleep();
  uint8_t rxInstruction = rxpacket[0];
  uint8_t sourceDeviceID = rxpacket[7];
  uint8_t destinationDevice = rxpacket[12];
  if(rxInstruction == INSTRUCTION_UPLOADED_CONFIRM && destinationDevice  == ThisDeviceInfo.EndDeviceID){
    UpdateTime(rxpacket);
  }
  Serial.println("Signal received!");
  for(uint8_t i = 0; i < rxsize; i++){
      Serial.printf("%d,", rxpacket[i]);
  }
  Serial.println();
  if(rxInstruction == INSTRUCTION_NETWORKING){
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
  if(rxInstruction == INSTRUCTION_NETWORKED_CONFIRM && destinationDevice == ThisDeviceInfo.EndDeviceID && !ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID]){
    ThisDeviceRoutingInfo.SonEndDeviceID[ThisDeviceRoutingInfo.SonEndDeviceNum] = rxpacket[7];
    ThisDeviceRoutingInfo.SonEndDeviceNum++;
    ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID] = 1;
    if(rxpacket[9] == 0) ThisDeviceRoutingInfo.SonEndDeviceIDAssigned[sourceDeviceID] = 0;
  }
  if(rxInstruction == INSTRUCTION_UPLOADING && destinationDevice == ThisDeviceInfo.EndDeviceID && !ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID]){
    ThisDeviceRoutingInfo.IfDeviceReceived[sourceDeviceID] = 1;
    ReadMonitorData(1);
    delay(500);
    for(uint8_t i = 0; i < 1; ++i){
      PreparePacket(INSTRUCTION_UPLOADED_CONFIRM, sourceDeviceID);
      Radio.Send( (uint8_t *)txPacket, BUFFER_SIZE );
      delay(200);
    }
  }
  if(rxInstruction == INSTRUCTION_UPLOADED_CONFIRM && destinationDevice == ThisDeviceInfo.EndDeviceID){
    ifNomalTransmitSuccess = 1;
  }
  if(rxInstruction == INSTRUCTION_ASSIGN_PRIORITY && destinationDevice == ThisDeviceInfo.EndDeviceID){
    ThisDeviceInfo.EndDevicePriority = rxpacket[9];
  }
}

void OnTxDone(){
  Serial.println("OnTxDone!");
  onTxDone = 1;
}

void OnTxTimeout()
{
    txtimeoutflag = 1;
    Serial.println("txtimeout!");
    printf("txtimeout");
    delay(10);
}