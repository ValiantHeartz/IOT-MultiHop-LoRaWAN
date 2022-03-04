#include <stdio.h>
#define BUFFER_SIZE                                 128

void EndDeviceInit(uint8_t EndDeviceID, uint8_t EndDeviceRank, uint16_t EndDeviceBattery);

typedef struct sEndDeviceInfo{
  uint8_t EndDeviceID;
  uint8_t EndDeviceRank;
  uint8_t EndDevicePriority;
  uint16_t EndDeviceBattery;
  //Channel parameters;
}EndDeviceInfo_t;

typedef struct sEndDeviceRoutingInfo{
  uint8_t NeiborFatherEndDeviceID[10];
  //uint8_t NeiborSonEndDevice[10];
  uint8_t FatherEndDeviceID;
  uint8_t SonEndDeviceID[10];
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
