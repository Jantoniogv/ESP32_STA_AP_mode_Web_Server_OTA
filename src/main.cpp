#include <Arduino.h>

#include "saveFlash.h"
#include "configInit.h"
#include "configWifi.h"
#include "wifi_connect.h"

#define _DEBUG_

void setup()
{

#ifdef _DEBUG_
  Serial.begin(115200);
#endif // _DEBUG_

  eraseFlash("config");

  //***** Configuracion del wifi *****//
  configWifi wifiData;

  if (!existKey("config", "reset"))
  {
    wifiData.saveChange();

#ifdef _DEBUG_
    Serial.println("Configuracion de red= " + readMemFlash("config", "config"));
    Serial.println("Configuracion de reset= " + readMemFlash("config", "reset"));
#endif
    saveMemFlash("config", "reset", "0");
  }
  else
  {

    bool reset = (bool)readMemFlash("config", "reset").toInt();

    if (reset)
    {
      wifiData.saveChange();

      saveMemFlash("config", "reset", "0");
    }
    else
    {

      String config = readMemFlash("config", "config");

      configWifi _wifiData(config);

      wifiData.setWifiType(_wifiData.getWifiType());

      wifiData.setSsidSTA(_wifiData.getSsidSTA());
      wifiData.setPassSTA(_wifiData.getPassSTA());
      wifiData.setSsidAP(_wifiData.getSsidAP());
      wifiData.setPassAP(_wifiData.getPassAP());

      wifiData.setHost(_wifiData.getHost());

      wifiData.setIPap(_wifiData.getIPap());

      wifiData.setIPsta(_wifiData.getIPsta());
      wifiData.setGateway(_wifiData.getGateway());
      wifiData.setSubnet(_wifiData.getSubnet());
    }
  }

  // Seteamos el modo de conexion
  setWifiMode(wifiData.getWifiType());

  // Iniciamos la conexion/es
  initWifi(wifiData.getSsidSTA(), wifiData.getPassSTA(), wifiData.getSsidAP(), wifiData.getPassAP());

  // Asignamos la IP del punto de acceso
  IPAddress IPap;
  IPap.fromString(wifiData.getIPap());

  wifiConfigAP(IPap);

  // Asignamos la IP del modo cliente en caso necesario
  if (wifiData.getWifiType() == WIFI_MODE_APSTA || wifiData.getWifiType() == WIFI_MODE_STA)
  {
    wifiConnectSTA();

    if (wifiData.getIPsta() != _IPsta)
    {
      IPAddress IP;
      IP.fromString(wifiData.getIPap());

      IPAddress gateway;
      gateway.fromString(wifiData.getGateway());

      IPAddress subnet;
      subnet.fromString(wifiData.getSubnet());

      wificConfigSTA(IP, gateway, subnet);
    }
  }
#ifdef _DEBUG_
  Serial.println("Configuracion de red= " + readMemFlash("config", "config"));
  Serial.println("Configuracion de reset= " + readMemFlash("config", "reset"));
#endif

  //***** Configuracion del servidor web *****//
}

void loop() {}