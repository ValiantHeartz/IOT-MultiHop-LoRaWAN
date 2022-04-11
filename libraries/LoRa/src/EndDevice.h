#include <stdio.h>
#include "LoRaWan_APP.h"
#include <TimeLib.h>

#define BUFFER_SIZE                                 51

void EndDeviceInit(uint8_t EndDeviceID, uint8_t EndDeviceRank, uint8_t EndDeviceBattery);

typedef struct sEndDeviceInfo{
  uint8_t EndDeviceID;
  uint8_t EndDeviceRank;
  uint8_t EndDevicePriority;
  uint8_t EndDeviceBattery;
  //Channel parameters;
}EndDeviceInfo_t;


typedef struct sFatherEndDevice{
  uint8_t FatherEndDeviceID;
  uint8_t FatherEndDevicePriority;
  uint8_t FatherEndDeviceBattery;
  uint8_t FatherEndDeviceRank;
  uint8_t FatherEndDeviceRSSI;
  uint8_t FatherEndDeviceSNR;
}FatherEndDevice_t;

typedef struct sEndDeviceRoutingInfo_t{
  uint8_t NeiborFatherEndDeviceNum;
  uint8_t FatherEndDeviceID;
  FatherEndDevice_t NeiborFatherEndDeviceInfo[10];
  uint8_t SonEndDeviceNum;
  uint8_t SonEndDeviceID[10];
  uint8_t IfDeviceReceived[20];
}EndDeviceRoutingInfo_t;

//EndDeviceCommand: Networking:0; Upload:1
typedef struct sEndDeviceTransmitData{
  EndDeviceInfo_t EndDeviceInfo;
  EndDeviceRoutingInfo_t EndDeviceRoutingInfo;
  uint8_t EndDeviceCommand;
  uint8_t EndDeviceTime[6];
  uint8_t EndDeviceBuffer[BUFFER_SIZE];
}EndDeviceTransmitData_t;

extern EndDeviceInfo_t ThisDeviceInfo;
extern EndDeviceRoutingInfo_t ThisDeviceRoutingInfo;
extern EndDeviceTransmitData_t ThisDeciveTransmitData;
extern uint8_t txPacket[BUFFER_SIZE];
extern TimerEvent_t wakeUp;
extern uint8_t ifTimeNotInit1;
extern uint8_t ifTimeNotInit2;
extern uint8_t ifTimeNotInit3;
extern uint8_t networkedFlag;
extern uint8_t LoRaWANModeFlag;
extern uint8_t networkingBroadcastnum;
extern uint8_t respondAckNum;
extern uint8_t startTime[6];
extern uint16_t setCycle;
extern bool ifNomalTransmitSuccess;
extern uint16_t rankIntervalTime;
extern uint8_t lorawanModeTryNum;
extern bool renetworkFlag;

extern uint8_t RadioIrqNum;
extern uint8_t RadioIrqTemp;
extern uint8_t rounds;

extern uint8_t confirmedNbTrials; //lorawan 1.0.2-18.4
extern uint8_t txPacket[BUFFER_SIZE];
extern uint8_t rxpacket[BUFFER_SIZE];
extern int16_t rssi, rxSize, snr;
extern uint8_t ENDDEVICEID;
extern const uint8_t VALIDDATAPOS;
extern uint8_t validDataPos;
extern uint8_t txPacket[BUFFER_SIZE];

void LoraRandomSend(uint8_t networkingBroadcastnum, uint8_t INSTRUCTION, uint8_t destinationID);
void LoraRandomNormalSend(uint8_t rankIntervalNum, uint8_t INSTRUCTION, uint8_t destinationID);
void PreparePacket(uint8_t insturction, uint8_t destinationDeviceID);
void SetLowPowerTimer(uint32_t sleeptime);
void WakeUpDevice();
uint8_t UpdateStartTime(uint8_t  *startTime, uint16_t setCycle);
void ReadMonitorData(uint8_t* txPacket);
void UpdateMonitorDataPos(bool ifNomalTransmitSuccess);
void OnTxDone();
void digitalClockDisplay();
bool checkUserAt(char *cmd, char *content);
void RadioIrqParaInit();
void LoRaPhyInit();
void LoRaWANPhyInit();
uint8_t ReadBattery();
void WAMPLInfoInit();
void SelectFatherEndDevice();
uint32_t CalcAllDeviceStartTime();
void MonitorDataInit();
void IfDeviceReceivedParaInit();
void OpenRadioDuration(uint16_t duration);
void RoutingInfoInit();
void UpdateTime(uint8_t* txPacket);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);