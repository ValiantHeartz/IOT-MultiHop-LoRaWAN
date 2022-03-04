#include "LoRaWan_APP.h"
#include "LoRa_APP.h"
#include "Arduino.h"

/*
 * set LoraWan_RGB to Active,the RGB active in loraWan
 * RGB red means sending;
 * RGB purple means joined done;
 * RGB blue means RxWindow1;
 * RGB yellow means RxWindow2;
 * RGB green means received done;
 */

/* OTAA para*/
uint8_t devEui[] = { 0x22, 0x32, 0x33, 0x00, 0x00, 0x88, 0x88, 0x02 };
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appKey[] = { 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x66, 0x01 };

/* ABP para*/
uint8_t nwkSKey[] = { 0xC1, 0x39, 0xFB, 0x90, 0x25, 0x3A, 0xD0, 0xD3, 0xD9, 0x00, 0x1E, 0x28, 0xFD, 0xF9, 0x47,0x52 };
uint8_t appSKey[] = { 0x61, 0x8B, 0x3F, 0x9E, 0x0E, 0x97, 0x3B, 0x97, 0x93, 0x5E, 0x39, 0x96, 0x9A, 0x0E, 0xF3,0x20 };
uint32_t devAddr =  ( uint32_t )0x2800F603;

/*LoraWan channelsmask, default channels 0-7*/ 
uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };

/*LoraWan region, select in arduino IDE tools*/
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t  loraWanClass = LORAWAN_CLASS;

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
/*!
* Number of trials to transmit the frame, if the LoRaMAC layer did not
* receive an acknowledgment. The MAC performs a datarate adaptation,
* according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
* to the following table:
*
* Transmission nb | Data Rate
* ----------------|-----------
* 1 (first)       | DR
* 2               | DR
* 3               | max(DR-1,0)
* 4               | max(DR-1,0)
* 5               | max(DR-2,0)
* 6               | max(DR-2,0)
* 7               | max(DR-3,0)
* 8               | max(DR-3,0)
*
* Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
* the datarate, in case the LoRaMAC layer did not receive an acknowledgment
*/
uint8_t confirmedNbTrials = 4;

/* Prepares the payload of the frame */
static void prepareTxFrame( uint8_t port )
{
	/*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
	*appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
	*if enabled AT, don't modify LORAWAN_APP_DATA_MAX_SIZE, it may cause system hanging or failure.
	*if disabled AT, LORAWAN_APP_DATA_MAX_SIZE can be modified, the max value is reference to lorawan region and SF.
	*for example, if use REGION_CN470, 
	*the max value for different DR can be found in MaxPayloadOfDatarateCN470 refer to DataratesCN470 and BandwidthsCN470 in "RegionCN470.h".
	*/
    appDataSize = 4;
    appData[0] = 0x00;
    appData[1] = 0x01;
    appData[2] = 0x02;
    appData[3] = 0x03;
}


void setup() {
	Serial.begin(115200);
	passthroughMode = true;
	enableAt(); 
#if(LORAWAN_DEVEUI_AUTO)
	LoRaWAN.generateDeveuiByChipID();
#endif
	getDevParam();
	printDevParam();
	deviceState = DEVICE_STATE_SLEEP;
	LoRaWAN.ifskipjoin();
	deviceState_lora = LORA_INIT;
	delay(5);
}

void loop()
{
	if(modeLoraWan)//loraWan mode(defalt;)
	{
	  switch( deviceState )
	  {
	    case DEVICE_STATE_INIT:
	    {
	      //Serial.printf("LoRaWan PassthroughMode start!\r\n");
	      //Serial.printf("please start with command\r\n");
	      getDevParam();
	      LoRaWAN.init(loraWanClass,loraWanRegion);
	      deviceState = DEVICE_STATE_JOIN;
	      break;
	    }
	    case DEVICE_STATE_JOIN:
	    {
	      LoRaWAN.join();
	      break;
	    }
	    case DEVICE_STATE_SEND:
	    {
	      LoRaWAN.send();
	      deviceState = DEVICE_STATE_SLEEP;
	      break;
	    }
	    case DEVICE_STATE_CYCLE:
	    {
	      // only used while joining
	      txDutyCycleTime = appTxDutyCycle + randr( 0, APP_TX_DUTYCYCLE_RND );
	      deviceState = DEVICE_STATE_SLEEP;
	      LoRaWAN.cycle(txDutyCycleTime);
	      break;
	    }
	    case DEVICE_STATE_SLEEP:
	    {
	      LoRaWAN.sleep();
	      break;
	    }
	    default:
	    {
	      deviceState = DEVICE_STATE_SLEEP;
	      break;
	    }
	  }
	}
	else//lora mode
	{
	  switch( deviceState_lora )
	  {
	    case LORA_INIT:
	    {
	      getDevParam();
	      LoRa.init();
	      deviceState_lora = MCU_SLEEP;
	      break;
	    }
	    case LORA_SEND:
	    {
	      LoRa.send();
	      deviceState_lora = MCU_SLEEP;
	      break;
	    }
	    case LORA_RECEIVE:
	    {
	      LoRa.receive();
	      deviceState_lora = MCU_SLEEP;
	      break;
	    }
	    case MCU_SLEEP:
	    {
	      LoRa.lowpower();
	      break;
	    }
	    default:
	    {
	      deviceState_lora = MCU_SLEEP;
	      break;
	    }
	  }
	}
}