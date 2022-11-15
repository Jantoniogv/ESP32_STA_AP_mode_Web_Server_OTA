#ifndef _WIFI_CONNECT_H
#define _WIFI_CONNECT_H

#include <Arduino.h>
#include <WiFi.h>

//#include "config.h"

#define DEBUG
#include "debugUtils.h"

bool setWifiMode(wifi_mode_t mode)
{
    return WiFi.mode(mode);
}

void initWifi(const char *ssidSTA, const char *passSTA,
              const char *ssidAP, const char *passAP)
{

    WiFi.begin(ssidSTA, passSTA);

    WiFi.softAP(ssidAP, passAP);

    DEBUG_PRINT("ESP32 ssidSTA: " + static_cast<String>(ssidSTA));

    DEBUG_PRINT("ESP32 passSTA: " + static_cast<String>(passSTA));

    DEBUG_PRINT("ESP32 ssidAP: " + static_cast<String>(ssidAP));

    DEBUG_PRINT("ESP32 passAP: " + static_cast<String>(passAP));

    DEBUG_PRINT("ESP32 IP as soft AP: " + WiFi.softAPIP().toString());
}

bool wifiConnectSTA()
{
    if (WiFi.status() != WL_CONNECTED)
    {

        DEBUG_PRINT("Connecting");

        int n = 0;
        while (WiFi.status() != WL_CONNECTED && n < 60)
        {
            delay(1000);
            DEBUG_PRINT(".");
            n++;
        }

        if (WiFi.status() == WL_CONNECTED)
        {

            DEBUG_PRINT("\nConnected...");
            DEBUG_PRINT("ESP32 IP on the WiFi network: " + WiFi.localIP().toString());
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool wificConfigSTA(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t)0x00000000, IPAddress dns2 = (uint32_t)0x00000000)
{

    WiFi.config(local_ip, gateway, subnet, dns1, dns2);
    WiFi.reconnect();

    return wifiConnectSTA();
}

bool wifiConfigAP(IPAddress ip, IPAddress subnet = IPAddress(255, 255, 255, 0))
{
    bool status = WiFi.softAPConfig(ip, ip, subnet);

    if (status)
    {
        DEBUG_PRINT("ESP32 IP as soft AP: " + WiFi.softAPIP().toString());

        return true;
    }
    else
    {
        return false;
    }
}

#endif //_WIFI_CONNECT_H