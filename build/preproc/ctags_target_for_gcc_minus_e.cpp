# 1 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
# 2 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 2
# 3 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 2






                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]


                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
# 25 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
/* OTAA para*/
uint8_t devEui[] = { 0x3F, 0x53, 0x01, 0x2A, 0x00, 0x00, 0x4D, 0x3B };
uint8_t appEui[] = { 0x81, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x01 };
uint8_t appKey[] = { 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x66, 0x01 };

/* ABP para 3B*/ //0xC1->C2
uint8_t nwkSKey[] = { 0xC2, 0x39, 0xFB, 0x90, 0x25, 0x3A, 0xD0, 0xD3, 0xD9, 0x00, 0x1E, 0x28, 0xFD, 0xF9, 0x47,0x52 };
uint8_t appSKey[] = { 0x61, 0x8B, 0x3F, 0x9E, 0x0E, 0x97, 0x3B, 0x97, 0x93, 0x5E, 0x39, 0x96, 0x9A, 0x0E, 0xF3,0x20 };
uint32_t devAddr = ( uint32_t )0x2800F603;

/* ABP para 3A*/
//uint8_t nwkSKey[] = { 0x37, 0x0B, 0xF7, 0x30, 0xB3, 0xE5, 0x70, 0xB7, 0x80, 0xC6, 0x8F, 0x44, 0xAA, 0xF8, 0xB5,0x00 };
//uint8_t appSKey[] = { 0x1A, 0xFE, 0xBB, 0x36, 0xF6, 0x4F, 0xB2, 0xD1, 0x04, 0xEF, 0x77, 0x13, 0x77, 0xB8, 0x5B,0x5F };
//uint32_t devAddr =  ( uint32_t )0x2800F602;

/*Variable init*/
uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };
uint8_t sendNum = 0;
static RadioEvents_t RadioEvents;

# 44 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
bool 
# 44 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
    sleepTimerExpired;
TimerEvent_t sleepTimer;
char txpacket[30 /* Define the payload size here*/];
char rxpacket[30 /* Define the payload size here*/];
static uint8_t counter=0;
double txNumber;

# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
bool 
# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
    requestack = 
# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
                 true
# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
                     ;
int16_t rssi,rxSize;
uint8_t LoRaWANModeFlag = 0;

/*Function declaration*/
static void lowPowerSleep(uint32_t sleeptime);
static void wakeUp();
void DoubleToString( char *str, double double_num,unsigned int len);
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );

void setup() {
    /*LoRaWAN init*/
 Serial.begin(115200);
    LoRaWAN.begin(CLASS_A, LORAMAC_REGION_AS923_AS1); //init LoRaMacInitialization -> init radioevents
    LoRaWAN.setAdaptiveDR(
# 64 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
                         true
# 64 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
                             );
    LoRaWAN.joinABP(nwkSKey, appSKey, devAddr);
    Serial.println("LoRaWAN Init Success!");

    for(sendNum = 0; sendNum < 5; sendNum++)
    {
        LoRaWAN.send(1, &counter, 1, requestack);
    }
    /*LoRa Phy init*/
    if(LoRaWANModeFlag == 0)
    {
        txNumber=0;
        rssi=0;
     RadioEvents.RxDone = OnRxDone;

        Radio.Init( &RadioEvents );
        Radio.SetChannel( 915000000 /* Hz*/ );
        Radio.SetTxConfig( MODEM_LORA, 14 /* dBm*/, 0, 0 /* [0: 125 kHz,*/,
                                   7 /* [SF7..SF12]*/, 1 /* [1: 4/5,*/,
                                   8 /* Same for Tx and Rx*/, 
# 83 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
                                                        false
# 83 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
                                                                                  ,
                                   
# 84 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
                                  true
# 84 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
                                      , 0, 0, 
# 84 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
                                              false
# 84 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
                                                                  , 3000 );
        Serial.println("LoRa Init Success!");
    }

}

void loop()
{
    lowPowerSleep(1500);
    counter++;
    txNumber += 0.01;
    if(LoRaWANModeFlag)
    {
        if (LoRaWAN.send(1, &counter, 1, requestack))
        {
            Serial.println("Gateway Send OK");
            delay(100);
            sendNum = 0;
        }
        else
        {
            Serial.println("Gateway Send FAILED");
            delay(100);
            sendNum++;
        }
    }
    else
    {
        sprintf(txpacket,"%s","Hello world number");
        DoubleToString(txpacket,txNumber,3);
        Radio.Send( (uint8_t *)txpacket, strlen(txpacket) );
        Serial.print(sendNum);
        Serial.println(" Node Send OK.");
        delay(100);
    }
}

static void lowPowerSleep(uint32_t sleeptime)
{
  sleepTimerExpired=
# 123 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
                   false
# 123 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
                        ;
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
  sleepTimerExpired=
# 135 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino" 3 4
                   true
# 135 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\myLoRa\\myLoRa.ino"
                       ;
}

void DoubleToString( char *str, double double_num,unsigned int len) {
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
    LoRaWANModeFlag = 1;

    rssi=rssi;
    rxSize=size;
    memcpy(rxpacket, payload, size );
    rxpacket[size]='\0';
    turnOnRGB(0x005000 /*color green, light 0x10*/,0);
    Radio.Sleep( );
    Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n",rxpacket,rssi,rxSize);

}
