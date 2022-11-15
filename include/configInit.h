#ifndef _CONFIGINIT_H_
#define _CONFIGINIT_H_
#include <Arduino.h>

#include <wifi.h>

wifi_mode_t initWifiType = WIFI_MODE_APSTA;

String initSsidSTA = "DIGIFIBRA-Ap99";
String initSsidAP = "MyESP32AP_2022";

String initPassSTA = "612018_2482019";
String initPassAP = "adminadmin";

String initHost = "ESP32_2022";

String initIPap = "192.168.10.1";

String initIPsta = "x.x.x.x";
String initGateway = "x.x.x.x";
String initSubnet = "x.x.x.x";

#endif //_CONFIGINIT_H_