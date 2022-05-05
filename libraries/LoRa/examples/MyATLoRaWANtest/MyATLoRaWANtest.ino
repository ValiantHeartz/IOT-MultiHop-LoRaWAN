#include "LoRaWan_APP.h"
//#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"
#include <TimeLib.h>
#include <Wire.h>
#include "HT_SH1107Wire.h"
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

//#define ENDDEVICEID 3
uint8_t ENDDEVICEID = 2;
uint16_t rankIntervalTime = 5000;
//static const uint16_t normalTransmitTime = 4000
/**************************************************************************************************************************/
/*LoRaWAN Mode Para*/
/* OTAA para*/
uint8_t devEui[] = {0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x04, 0xEF, 0xB9};
uint8_t appEui[] = {0x81, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x01};
uint8_t appKey[] = {0xD9, 0x0A, 0x1C, 0xD7, 0xE0, 0x88, 0x9A, 0x4C, 0x54, 0xEA, 0x4B, 0x56, 0x40, 0x47, 0x37, 0xBB};

/* ABP para:3B*/ //c1-c2
uint8_t nwkSKey[] = {0xC2, 0x39, 0xFB, 0x90, 0x25, 0x3A, 0xD0, 0xD3, 0xD9, 0x00, 0x1E, 0x28, 0xFD, 0xF9, 0x47, 0x52};
uint8_t appSKey[] = {0x61, 0x8B, 0x3F, 0x9E, 0x0E, 0x97, 0x3B, 0x97, 0x93, 0x5E, 0x39, 0x96, 0x9A, 0x0E, 0xF3, 0x20};
uint32_t devAddr = (uint32_t)0x2800F603;

/* ABP para:3a*/ //37-38
// uint8_t nwkSKey[] = {0x37, 0x0B, 0xF7, 0x30, 0xB3, 0xE5, 0x70, 0xB7, 0x80, 0xC6, 0x8F, 0x44, 0xAA, 0xF8, 0xB5, 0x00};
// uint8_t appSKey[] = {0x1A, 0xFE, 0xBB, 0x36, 0xF6, 0x4F, 0xB2, 0xD1, 0x04, 0xEF, 0x77, 0x13, 0x77, 0xB8, 0x5B, 0x5F};
// uint32_t devAddr = (uint32_t)0x2800F602;

/*abp ttn*/
// uint8_t nwkSKey[] = {0x8D, 0x47, 0x77, 0x25, 0x91, 0x1B, 0xBE, 0x88, 0x38, 0x81, 0x26, 0x7A, 0x51, 0x15, 0xD3, 0x75};
// uint8_t appSKey[] = {0x55, 0x78, 0x2A, 0x3B, 0xE9, 0x6D, 0x2C, 0x31, 0x44, 0xDF, 0xB8, 0x36, 0xE9, 0x8D, 0x9A, 0xEC};
// uint32_t devAddr = (uint32_t)0x260BFFCF;

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
int16_t rssi = 0, rxSize = 0, snr = 0;
uint8_t loRaLWJudgeFlag = 0;
uint8_t rounds = 0;
uint8_t nextNetworkingPeriod = 10;
extern uint8_t loRaWANReceiveFlag;
extern SH1107Wire  display;
/**************************************************************************************************************************/
/*Functions*/
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

/**************************************************************************************************************************/
/*Main Function*/
void setup()
{
  Serial.begin(115200);
#if (AT_SUPPORT)
  enableAt();
#endif
  /*Wait for Time Init*/
  //while(ifTimeNotInit1||ifTimeNotInit2||ifTimeNotInit3) lowPowerHandler();
  Serial.println("Time init success!");
  /*LoRaWAN Mode Init*/
  TimerInit( &wakeUp, WakeUpDevice );
  SetLowPowerTimer(CalcAllDeviceStartTime());
  WAMPLInfoInit();
  LoRaPhyInit();
}
uint16_t radionum = 1;
void loop()
{
    Radio.Rx( 0 );
    Radio.IrqProcess( );
    delay(50);
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    // rssi=rssi;
    rxSize=size;
    for(uint8_t i = 0; i < rxSize; ++i){
        rxpacket[i] = payload[i];
    }
    //memcpy(rxpacket, payload, rxSize );
    //Serial.print(rxpacket[0]);
    Serial.println(radionum++);
    for(uint8_t i = 0; i < rxSize; ++i){
        Serial.print(rxpacket[i]);Serial.print(',');
    }
    Serial.println();
    // rxpacket[size]='\0';
    // //turnOnRGB(COLOR_RECEIVED,0);
    // Radio.Sleep( );
    // Serial.println();
    // Serial.println(radionum++);
    // Serial.printf("Instruction: %d", rxpacket[0]);
    // Serial.println();
    // Serial.printf("Father ID: %d", rxpacket[11]);
    // Serial.println();
    // Serial.printf("Destination ID: %d", rxpacket[12]);
    // Serial.println();
    // Serial.printf("Source ID: %d", rxpacket[7]);
    // Serial.println();
    // Serial.printf("Battery level(%): %d", rxpacket[10]*100/70);
    // Serial.println();
    // Serial.print("Send time: ");
    // for(uint8_t i = 1; i < 7; i++){
    //   Serial.printf("%d ", rxpacket[i]);
    // }
    // Serial.println();
    // Serial.printf("Data buffer: ");
    // uint8_t t = 13;
    // while(rxpacket[t]!=255 && t <size){
    //     Serial.printf("%d ", rxpacket[t]);
    //     t++;
    // }
    // Serial.println();
    // Serial.printf("Packet size is %d. ", size);Serial.println();
    
    // char s[30];
    // char temp[10];
    // strcat(s, "ID: ");
    // itoa(payload[7], temp, 10);
    // strcat(s, temp);
    // char temp2[10] = " RSSI: ";
    // strcat(s, temp2);
    // itoa(rssi, temp, 10);
    // strcat(s, temp);
    // OLEDDispaly(s);
}


void OLEDDispaly(char* s){
    digitalWrite(Vext,LOW);
    display.init();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.clear();
    display.drawString(91, 22, s);
    display.display();
    delay(100);
    // display.clear();
    // display.drawString(58, 22, "No Signal...");
    // display.display();
}
//  