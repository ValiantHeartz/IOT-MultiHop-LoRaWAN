#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"
#include "C:\Users\zhoul\AppData\Local\Arduino15\packages\CubeCell\hardware\CubeCell\1.3.0\cores\asr6601\lora\driver\rtc-board.h"
#include <TimeLib.h>

#define RF_FREQUENCY                                915000000 // Hz
#define TX_OUTPUT_POWER                             14        // dBm 22+-1dbm
#define LORA_BANDWIDTH                              0         // [0: 125 kHz,1: 250 kHz,2: 500 kHz,3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12] 10kb/s-0.5kb/s
#define LORA_CODINGRATE                             1         // [1: 4/5,2: 4/6,3: 4/7,4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false
#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 50 // Define the payload size here.  { 51, 51, 51, 115, 222, 222 };

/* OTAA para*/
uint8_t devEui[] = { 0x3F, 0x53, 0x01, 0x2A, 0x00, 0x00, 0x4D, 0x3B };
uint8_t appEui[] = { 0x81, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x01 };
uint8_t appKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* ABP para 3B*/ //c1-c2
uint8_t nwkSKey[] = { 0xC1, 0x39, 0xFB, 0x90, 0x25, 0x3A, 0xD0, 0xD3, 0xD9, 0x00, 0x1E, 0x28, 0xFD, 0xF9, 0x47,0x52 };
uint8_t appSKey[] = { 0x61, 0x8B, 0x3F, 0x9E, 0x0E, 0x97, 0x3B, 0x97, 0x93, 0x5E, 0x39, 0x96, 0x9A, 0x0E, 0xF3,0x20 };
uint32_t devAddr =  ( uint32_t )0x2800F603;

/* ABP para 3A*/ 
//uint8_t nwkSKey[] = { 0x37, 0x0B, 0xF7, 0x30, 0xB3, 0xE5, 0x70, 0xB7, 0x80, 0xC6, 0x8F, 0x44, 0xAA, 0xF8, 0xB5,0x00 };
//uint8_t appSKey[] = { 0x1A, 0xFE, 0xBB, 0x36, 0xF6, 0x4F, 0xB2, 0xD1, 0x04, 0xEF, 0x77, 0x13, 0x77, 0xB8, 0x5B,0x5F };
//uint32_t devAddr =  ( uint32_t )0x2800F602;

/*Variable init*/
uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };
static RadioEvents_t RadioEvents;
bool sleepTimerExpired;
TimerEvent_t sleepTimer;
uint8_t txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];
static uint8_t counter=0;
double txNumber;
bool requestack = true;
int16_t rssi,rxSize;
uint8_t LoRaWANModeFlag = 0;
//RtcCalendar_t EndDeviceTime; 


/*Function declaration*/
static void lowPowerSleep(uint32_t sleeptime);
static void wakeUp();
void  DoubleToString( char *str, double double_num,unsigned int len);
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );
void digitalClockDisplay();
void printDigits(int digits);

void setup() {
    Serial.begin(115200);
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        txpacket[i] = i;
    }
    /*LoRaWAN init*/
    LoRaWAN.begin(LORAWAN_CLASS, ACTIVE_REGION);  //init LoRaMacInitialization -> init radioevents
    LoRaWAN.setAdaptiveDR(true);
    LoRaWAN.joinABP(nwkSKey, appSKey, devAddr);
    int result = LoRaWAN.send(BUFFER_SIZE, txpacket, 1, requestack);
    Serial.print("result: ");
    Serial.println(result);
    if(LoRaWAN.send(BUFFER_SIZE, txpacket, 1, requestack))
    {
        Serial.println("LoRaWAN Init Success!");
        delay(100);
        LoRaWANModeFlag = 1;
    }
    /*LoRa Phy init*/
    if(LoRaWANModeFlag == 0)
    {
        txNumber=0;
        rssi=0;
	    RadioEvents.RxDone = OnRxDone;

        Radio.Init( &RadioEvents );
        Radio.SetChannel( RF_FREQUENCY );
        Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                                   LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                                   LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                                   true, 0, 0, LORA_IQ_INVERSION_ON, 3000 );
        Serial.println("LoRa Init Success!");
    }
    
}

void loop()
{
    digitalClockDisplay();
    delay(10);
    lowPowerSleep(1000);
    if(1)
    {
      LoRaWAN.send(BUFFER_SIZE, txpacket, 1, requestack);
        // if (LoRaWAN.send(BUFFER_SIZE, txpacket, 1, requestack))
        // {
        //     Serial.println("Gateway Send OK");
        //     delay(100);
        // }
        // else
        // {
        //     Serial.println("Gateway Send FAILED");
        //     delay(100);
        // }
    }  
    else
    {
        Radio.Send(txpacket, sizeof(txpacket)/sizeof(uint8_t) );
        //EndDeviceTime = (uint64_t)(TimerGetCurrentTime( ));
        //frac = modf((double)(endDeviceTime), &inter);
        //Serial.print(txpacket);
       // EndDeviceTime = RtcGetCalendar();
        Serial.print(txpacket[0]);
        Serial.print(sizeof(txpacket)/sizeof(uint8_t));
        Serial.println(" Node Send OK.");
        delay(100);
    }
}

static void lowPowerSleep(uint32_t sleeptime)
{
  sleepTimerExpired=false;
  TimerInit( &sleepTimer, &wakeUp );
  TimerSetValue( &sleepTimer, sleeptime );
  TimerStart( &sleepTimer );
  //Low power handler also gets interrupted by other timers
  //So wait until our timer had expired
  while (!sleepTimerExpired) lowPowerHandler();  
  TimerStop( &sleepTimer );  
}

static void wakeUp()
{
  sleepTimerExpired=true;
}

void  DoubleToString( char *str, double double_num,unsigned int len) { 
  double fractpart, intpart;
  fractpart = modf(double_num, &intpart);
  fractpart = fractpart * (pow(10,len));
  sprintf(str + strlen(str),"%d", (int)(intpart)); //Integer part
  sprintf(str + strlen(str), ".%d", (int)(fractpart)); //Decimal part
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    uint8_t pktHeaderLen = 0;
    LoRaMacHeader_t macHdr;
    macHdr.Value = payload[pktHeaderLen++];
    switch ( macHdr.Bits.MType ) {
        case FRAME_TYPE_DATA_UNCONFIRMED_DOWN: {
            Serial.printf("receive downlink success!");
        }
    }
    LoRaWANModeFlag = 0;

    rssi=rssi;
    rxSize=size;
    memcpy(rxpacket, payload, size );
    rxpacket[size]='\0';
    turnOnRGB(COLOR_RECEIVED,0);
    Radio.Sleep( );
    Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n",rxpacket,rssi,rxSize);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}