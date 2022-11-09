#ifndef _CONFIGINIT_H_
#define _CONFIGINIT_H_
#include <Arduino.h>

#include <wifi.h>

wifi_mode_t _wifiType = WIFI_MODE_APSTA;

String _ssidSTA = "DIGIFIBRA-Ap99";
String _ssidAP = "MyESP32AP_2022";

String _passSTA = "612018_2482019";
String _passAP = "adminadmin";

String _host = "ESP32_2022";

String _IPap = "192.168.10.1";
String _IPsta = "0.0.0.0";
String _gateway = "0.0.0.0";
String _subnet = "0.0.0.0";

bool reset = 1;

#endif //_CONFIG_H_