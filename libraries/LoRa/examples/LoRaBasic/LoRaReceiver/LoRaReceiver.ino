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

/*
 * set LoraWan_RGB to 1,the RGB active in loraWan
 * RGB red means sending;
 * RGB green means received done;
 */
#ifndef LoraWan_RGB
#define LoraWan_RGB 0
#endif

#define RF_FREQUENCY                                915000000 // Hz

#define TX_OUTPUT_POWER                             10        // dBm

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
#define BUFFER_SIZE                                 51 // Define the payload size here

char txpacket[BUFFER_SIZE];
uint8_t rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;

int16_t txNumber;

int16_t rssi,rxSize;
extern SH1107Wire  display;

void setup() {
    Serial.begin(115200);

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

void loop()
{
    Radio.Rx( 0 );
    delay(50);
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    rssi=rssi;
    rxSize=size;
    memcpy(rxpacket, payload, size );
    rxpacket[size]='\0';
    //turnOnRGB(COLOR_RECEIVED,0);
    Radio.Sleep( );
    Serial.print("send time:");
    //Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n",rxpacket,rssi,rxSize);
    for(uint8_t i = 0; i < size; i++){
      Serial.printf("%d,", rxpacket[i]);
    }
    Serial.print("receive time:");
    Serial.printf("%d,%d", minute(), second());
    Serial.println();
    char s[40];
    char temp[10];
    strcat(s, "ID: ");
    itoa(payload[7], temp, 10);
    strcat(s, temp);
    char temp2[10] = " RSSI: ";
    strcat(s, temp2);
    itoa(rssi, temp, 10);
    strcat(s, temp);
    OLEDDispaly(s);
}


void OLEDDispaly(char* s){
    digitalWrite(Vext,LOW);
    display.init();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.clear();
    display.drawString(58, 22, s);
    display.display();
    delay(1000);
    // display.clear();
    // display.drawString(58, 22, "No Signal...");
    // display.display();
}

