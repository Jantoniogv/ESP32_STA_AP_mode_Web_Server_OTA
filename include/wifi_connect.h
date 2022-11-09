#ifndef _WIFI_CONNECT_H
#define _WIFI_CONNECT_H

#include <Arduino.h>
#include <WiFi.h>

#define _DEBUG_

bool setWifiMode(wifi_mode_t mode)
{
    return WiFi.mode(mode);
}

void initWifi(const char *ssidSTA, const char *passSTA,
              const char *ssidAP, const char *passAP)
{

    WiFi.begin(ssidSTA, passSTA);

    WiFi.softAP(ssidAP, passAP);

#ifdef _DEBUG_
    Serial.print("ESP32 ssidSTA: ");
    Serial.println(ssidSTA);

    Serial.print("ESP32 passSTA: ");
    Serial.println(passSTA);

    Serial.print("ESP32 ssidAP: ");
    Serial.println(ssidAP);

    Serial.print("ESP32 passAP: ");
    Serial.println(passAP);

    Serial.print("ESP32 IP as soft AP: ");
    Serial.println(WiFi.softAPIP());
#endif // _DEBUG_
}

bool wifiConnectSTA()
{
    if (WiFi.status() != WL_CONNECTED)
    {

#ifdef _DEBUG_
        Serial.print("Connecting");
#endif // _DEBUG_

        int n = 0;
        while (WiFi.status() != WL_CONNECTED && n < 60)
        {
            delay(1000);
            Serial.print(".");
            n++;
        }

        if (WiFi.status() == WL_CONNECTED)
        {

#ifdef _DEBUG_
            Serial.println("\nConnected...");
            Serial.print("ESP32 IP on the WiFi network: ");
            Serial.println(WiFi.localIP());
#endif // _DEBUG_
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

#ifdef _DEBUG_
        Serial.print("ESP32 IP as soft AP: ");
        Serial.println(WiFi.softAPIP());
#endif // _DEBUG_

        return true;
    }
    else
    {
        return false;
    }
}

#endif //_WIFI_CONNECT_H