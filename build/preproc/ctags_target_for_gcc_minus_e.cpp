# 1 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
# 2 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
//#include "LoRaWanMinimal_APP.h"
# 4 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
# 5 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
# 6 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2
# 7 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 2

/**************************************************************************************************************************/
/*LoRa Mode Para*/
# 22 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
/**************************************************************************************************************************/
/*LoRaWAN Mode Para*/
/* OTAA para*/
uint8_t devEui[] = {0x3F, 0x53, 0x01, 0x2A, 0x00, 0x00, 0x4D, 0x3B};
uint8_t appEui[] = {0x81, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x01};
uint8_t appKey[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* ABP para*/ //c1-c2
uint8_t nwkSKey[] = {0xC2, 0x39, 0xFB, 0x90, 0x25, 0x3A, 0xD0, 0xD3, 0xD9, 0x00, 0x1E, 0x28, 0xFD, 0xF9, 0x47, 0x52};
uint8_t appSKey[] = {0x61, 0x8B, 0x3F, 0x9E, 0x0E, 0x97, 0x3B, 0x97, 0x93, 0x5E, 0x39, 0x96, 0x9A, 0x0E, 0xF3, 0x20};
uint32_t devAddr = (uint32_t)0x2800F603;

/*LoraWan channelsmask, default channels 0-7*/
uint16_t userChannelsMask[6] = {0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/*LoraWan region, select in arduino IDE tools*/
LoRaMacRegion_t loraWanRegion = LORAMAC_REGION_CN470;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t loraWanClass = CLASS_A;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 15000;

/*OTAA or ABP*/

# 47 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 47 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    overTheAirActivation = 
# 47 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                           false
# 47 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                          ;

/*ADR enable*/

# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    loraWanAdr = 
# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                 true
# 50 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                            ;

/* set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again */

# 53 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 53 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    keepNet = 
# 53 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
              false
# 53 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                 ;

/* Indicates if the node is sending confirmed or unconfirmed messages */

# 56 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 56 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    isTxConfirmed = 
# 56 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                    true
# 56 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                      ;

/* Application port */
uint8_t appPort = 2;

/**************************************************************************************************************************/
/*This File Variables*/
uint8_t confirmedNbTrials = 4; //lorawan 1.0.2-18.4
uint8_t txpacket[115 /* Define the payload size here.  { 51, 51, 51, 115, 222, 222 };*/];
uint8_t rxpacket[115 /* Define the payload size here.  { 51, 51, 51, 115, 222, 222 };*/];
int16_t rssi = 0, rxSize = 0, snr = 0;
static RadioEvents_t RadioEvents;
uint8_t lorawanModeTryNum = 4;
extern uint8_t RadioIrqNum;
extern uint8_t RadioIrqTemp;
uint8_t LoRaWANModeFlag = 0;
uint8_t EndDeviceID = 1;
uint8_t batteryVoltage = 0;

/**************************************************************************************************************************/
/*Functions*/
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void digitalClockDisplay();
void printDigits(int digits);

# 80 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 80 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    checkUserAt(char *cmd, char *content);
static void prepareTxFrame(uint8_t port);
void RadioIrqParaInit();
void LoRaPhyInit();
uint16_t ReadBattery();
void WAMPLInfoInit();

/**************************************************************************************************************************/
/*Main Function*/
void setup()
{
  Serial.begin(115200);




  // /*LoRaWAN Mode Init*/
  // LoRaWAN.init(LORAWAN_CLASS, ACTIVE_REGION);
  // LoRaWAN.join(); //abp
  // while (lorawanModeTryNum--)
  // {
  //   LoRaWAN.sendrequestconfirm(BUFFER_SIZE, txpacket, 1, 1);
  //   delay(1000);
  //   Serial.print("RadioIrqNum:");
  //   Serial.println(RadioIrqNum);
  //   if (RadioIrqNum == 2)
  //   {
  //     LoRaWANModeFlag = 1;
  //     Serial.println("LoRaWAN Init Success!");
  //     break;
  //   }
  // }

  /*LoRa Phy Init*/
  if (!LoRaWANModeFlag)
  {
    LoRaPhyInit();
    Serial.println("LoRa Init Success!");
  }
  /*WAMPL(Wide Area Multi-hop Protocol in LoRaWAN) Init*/
  WAMPLInfoInit();
}

void loop()
{
  digitalClockDisplay();
  delay(2000);
  if (LoRaWANModeFlag)
  {
    RadioIrqParaInit();
    LoRaWAN.sendrequestconfirm(115 /* Define the payload size here.  { 51, 51, 51, 115, 222, 222 };*/, txpacket, 1, 1);
    delay(100);
    Serial.print("RadioIrqNum:");
    Serial.println(RadioIrqNum);
  }
  else{
    Serial.println("loramode");
    batteryVoltage = ReadBattery();
    Serial.print(ThisDeviceInfo.EndDeviceBattery);
    Serial.print(", ");
    Serial.println(batteryVoltage);
  }
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
  LoRaWANModeFlag = 1;

  rssi = rssi;
  rxSize = size;
  memcpy(rxpacket, payload, size);
  rxpacket[size] = '\0';
  turnOnRGB(0x005000 /*color green, light 0x10*/, 0);
  Radio.Sleep();
  Serial.printf("\r\nreceive packet \"%s\" with rssi %d , length %d\r\n", rxpacket, rssi, rxSize);
}

void digitalClockDisplay()
{
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

void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

//AT+setime=110403332022
//11:04:03 3 3 2022

# 193 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
bool 
# 193 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
    checkUserAt(char *cmd, char *content)
{
  char temp[2];
  if (strcmp(cmd, "setime") == 0)
  {
    for (int i = 0; i < strlen(content); i++)
    {
      Serial.printf("%c", content[i]);
    }
    Serial.println();
    setTime(atoi(strncpy(temp, content, 2)), atoi(strncpy(temp, content + 2, 2)), atoi(strncpy(temp, content + 4, 2)), atoi(strncpy(temp, content + 6, 2)),
            atoi(strncpy(temp, content + 8, 2)), atoi(strncpy(temp, content + 10, 4)));
    return 
# 205 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
          true
# 205 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
              ;
  }
  return 
# 207 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
        false
# 207 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
             ;
}

/* Prepares the payload of the frame */
static void prepareTxFrame(uint8_t port)
{
  appDataSize = 4; //appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h". max = 128
  appData[0] = 0x00;
  appData[1] = 0x01;
  appData[2] = 0x02;
  appData[3] = 0x03;
}

void RadioIrqParaInit()
{
  RadioIrqNum = 0;
  RadioIrqTemp = 0;
}
void LoRaPhyInit()
{
  RadioEvents.RxDone = OnRxDone;

  Radio.Init(&RadioEvents);
  Radio.SetChannel(915000000 /* Hz*/);
  Radio.SetTxConfig(MODEM_LORA, 14 /* dBm 22+-1dbm*/, 0, 0 /* [0: 125 kHz,1: 250 kHz,2: 500 kHz,3: Reserved]*/,
                    7 /* [SF7..SF12] 10kb/s-0.5kb/s*/, 1 /* [1: 4/5,2: 4/6,3: 4/7,4: 4/8]*/,
                    8 /* Same for Tx and Rx*/, 
# 233 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                                         false
# 233 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                                                   ,
                    
# 234 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                   true
# 234 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                       , 0, 0, 
# 234 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino" 3 4
                               false
# 234 "c:\\Users\\zhoul\\AppData\\Local\\Arduino15\\packages\\CubeCell\\hardware\\CubeCell\\1.3.0\\libraries\\LoRa\\examples\\MyATLoRaWAN\\MyATLoRaWAN.ino"
                                                   , 3000);
}

uint16_t ReadBattery(){
  uint16_t batteryVoltage;
  pinMode(P3_3,OUTPUT);
  digitalWrite(P3_3,LOW);
  batteryVoltage = analogRead(P2_0)*2;
  pinMode(P3_3,INPUT);
  return batteryVoltage;
}

void WAMPLInfoInit(){
  EndDeviceInit(EndDeviceID, 0, ReadBattery());
}
