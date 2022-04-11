/* Heltec Automation send communication test example
 *
 * Function:
 * 1. Send data from a CubeCell device over hardware 
 * 
 * 
 * this project also realess in GitHub:
 * https://github.com/HelTecAutomation/ASR650x-Arduino
 * */

#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <TimeLib.h>

/*
 * set LoraWan_RGB to 1,the RGB active in loraWan
 * RGB red means sending;
 * RGB green means received done;
 */
#ifndef LoraWan_RGB
#define LoraWan_RGB 0
#endif

#define RF_FREQUENCY                                471900000 // Hz 471900000

#define TX_OUTPUT_POWER                             20       // dBm 10,14,17,20

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
#define BUFFER_SIZE                                 30 // Define the payload size here

uint8_t txpacket[BUFFER_SIZE];
uint8_t rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;
void RadioIrqParaInit();

double txNumber;

int16_t rssi,rxSize;
void  DoubleToString( char *str, double double_num,unsigned int len);

void setup() {
    Serial.begin(115200);

    txNumber=0;
    rssi=0;
    RadioEvents.RxDone = OnRxDone;
    Radio.Init( &RadioEvents );
    Radio.SetChannel( RF_FREQUENCY );
    Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                                   LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                                   LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                                   true, 0, 0, LORA_IQ_INVERSION_ON, 3000 ); 
   }


uint8_t num = 0;
void loop()
{

  txpacket[0] = minute();
  txpacket[1] = second();
  txpacket[7] = num++;
  Serial.printf("%d,%d", minute(), second());
  turnOnRGB(COLOR_SEND,10);
	Radio.Send( (uint8_t *)txpacket, sizeof(txpacket)/sizeof(uint8_t) ); //send the package out
  delay(100);
  	
}

/**
  * @brief  Double To String
  * @param  str: Array or pointer for storing strings
  * @param  double_num: Number to be converted
  * @param  len: Fractional length to keep
  * @retval None
  */
void  DoubleToString( char *str, double double_num,unsigned int len) { 
  double fractpart, intpart;
  fractpart = modf(double_num, &intpart);
  fractpart = fractpart * (pow(10,len));
  sprintf(str + strlen(str),"%d", (int)(intpart)); //Integer part
  sprintf(str + strlen(str), ".%d", (int)(fractpart)); //Decimal part
}

// 	delay(10);
// 	txNumber += 0.01;
// 	sprintf(txpacket,"%s","Hello world number");  //start a package
// //	sprintf(txpacket+strlen(txpacket),"%d",txNumber); //add to the end of package
	
// 	DoubleToString(txpacket,txNumber,3);	   //add to the end of package
	
// 	turnOnRGB(COLOR_SEND,0); //change rgb color

// 	Serial.printf("\r\nsending packet \"%s\" , length %d\r\n",txpacket, strlen(txpacket));

// void RadioIrqParaInit()
// {
//   RadioIrqNum = 0;
//   RadioIrqTemp = 0;
//   onTxDone = 0;
// }

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    rssi=rssi;
    rxSize=size;
    memcpy(rxpacket, payload, size );
    rxpacket[size]='\0';
    turnOnRGB(COLOR_RECEIVED,0);
    Radio.Sleep( );
    // Serial.print("send time:");
    // //Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n",rxpacket,rssi,rxSize);
    // for(uint8_t i = 0; i < size; i++){
    //   Serial.printf("%d,", rxpacket[i]);
    // }
    Serial.print("receive time:");
    Serial.printf("%d,%d", minute(), second());
    Serial.println();
}
