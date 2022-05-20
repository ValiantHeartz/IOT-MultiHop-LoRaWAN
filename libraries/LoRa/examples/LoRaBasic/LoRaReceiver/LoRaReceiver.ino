/* Heltec Automation Receive communication test example
 *
 * Function:
 * 1. Receive the same frequency band lora signal program
 * 
 * 
 * this project also realess in GitHub:
 * https://github.com/HelTecAutomation/ASR650x-Arduino
 * */

#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <TimeLib.h>
#include "HT_SH1107Wire.h"
#include "C:\Users\zhoul\AppData\Local\Arduino15\packages\CubeCell\hardware\CubeCell\1.3.0\libraries\LoRa\src\EndDevice.h"

/*
 * set LoraWan_RGB to 1,the RGB active in loraWan
 * RGB red means sending;
 * RGB green means received done;
 */
#ifndef LoraWan_RGB
#define LoraWan_RGB 0
#endif

#define RF_FREQUENCY                                470000000 // Hz

#define TX_OUTPUT_POWER                             20        // dBm

#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false


#define RX_TIMEOUT_VALUE                            1000
//#define BUFFER_SIZE                                 51 // Define the payload size here

uint8_t txPacket[BUFFER_SIZE];
uint8_t rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;

int16_t txNumber;

int16_t rssi;
uint16_t rxSize;
extern SH1107Wire  display;

void setup() {
    Serial.begin(115200);

    //enableAt();

    txNumber=0;
    rssi=0;
	
	  RadioEvents.RxDone = OnRxDone;
    Radio.Init( &RadioEvents );        //from radio.h
    Radio.SetChannel( RF_FREQUENCY );
	
	Radio.SetRxConfig( MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                                   LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                                   LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                                   0, true, 0, 0, LORA_IQ_INVERSION_ON, true );
   //turnOnRGB(COLOR_SEND,0); //change rgb color
   Serial.println("into RX mode");
   }


void OLEDDispaly(char* s);
bool rxtx =1;
bool rxflag = 0;
uint16_t radionum = 1;
uint32_t time1 = 0;
void loop()
{
    
    Radio.Rx(0);
    while(1){
        //Radio.IrqProcess();
    }
    
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    rxSize=size;
    for(uint8_t i = 0; i < rxSize; ++i){
        //Serial.print(payload[i]);Serial.print(',');
        rxpacket[i] = payload[i];
    }
    //Radio.Sleep( );
    Serial.println();
    Serial.println(radionum++);
    Serial.printf("Instruction: %d", rxpacket[0]);
    Serial.println();
    Serial.printf("Father ID: %d", rxpacket[11]);
    Serial.println();
    Serial.printf("Destination ID: %d", rxpacket[12]);
    Serial.println();
    Serial.printf("Source ID: %d", rxpacket[7]);
    Serial.println();
    Serial.printf("Battery level(%): %d", rxpacket[10]*100/70);
    Serial.println();
    Serial.print("Send time: ");
    for(uint8_t i = 1; i < 7; i++){
      Serial.printf("%d ", rxpacket[i]);
    }
    Serial.println();
    Serial.printf("Data buffer: ");
    uint8_t t = 13;
    while(rxpacket[t]!=255 && t <rxSize){
        Serial.printf("%d ", rxpacket[t]);
        t++;
    }
    Serial.println();
    Serial.printf("Packet size is %d. ", rxSize);Serial.println();
    // delay(1000);
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

// void loop()
// {
// 	Radio.Rx( 0 );
//   delay(500);
//   Radio.IrqProcess( );
// }

// void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
// {
//     rssi=rssi;
//     rxSize=size;
//     memcpy(rxpacket, payload, size );
//     rxpacket[size]='\0';
//     //turnOnRGB(COLOR_RECEIVED,0);
//     Radio.Sleep( );
//     Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n",rxpacket,rssi,rxSize);

// }
