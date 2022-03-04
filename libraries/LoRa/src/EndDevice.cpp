#include "EndDevice.h"

EndDeviceInfo_t ThisDeviceInfo;
EndDeviceRoutingInfo_t ThisDeviceRoutingInfo;
EndDeviceTransmitData_t ThisDeciveTransmitData;

void EndDeviceInit(uint8_t EndDeviceID, uint8_t EndDeviceRank, uint16_t EndDeviceBattery)
{
    ThisDeviceInfo.EndDeviceID = EndDeviceID;
    ThisDeviceInfo.EndDeviceRank = EndDeviceRank;
    ThisDeviceInfo.EndDevicePriority = 0;
    ThisDeviceInfo.EndDeviceBattery = EndDeviceBattery;
}





