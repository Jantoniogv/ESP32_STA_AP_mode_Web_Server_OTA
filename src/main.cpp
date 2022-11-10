#include <Arduino.h>

#include "saveFlash.h"
#include "configInit.h"
#include "config.h"
#include "wifi_connect.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#define DEBUG
#include "debugUtils.h"

AsyncWebServer server(80);

void setup()
{

  // Inicializa la conexion serial
  Serial.begin(115200);

  eraseFlash("config");

  // Inicializa el objeto con la variables de configuracion
  Config configData;

  // Seteamos el modo de conexion
  setWifiMode(configData.getWifiType());

  // Iniciamos la conexion/es
  initWifi(configData.getSsidSTA(), configData.getPassSTA(), configData.getSsidAP(), configData.getPassAP());

  // Asignamos la IP del punto de acceso
  IPAddress IPap;
  IPap.fromString(configData.getIPap());

  wifiConfigAP(IPap);

  // Asignamos la IP del modo cliente en caso necesario
  if (configData.getWifiType() == WIFI_MODE_APSTA || configData.getWifiType() == WIFI_MODE_STA)
  {
    wifiConnectSTA();

    if (configData.getIPsta() != initIPsta)
    {
      IPAddress IP;
      IP.fromString(configData.getIPap());

      IPAddress gateway;
      gateway.fromString(configData.getGateway());

      IPAddress subnet;
      subnet.fromString(configData.getSubnet());

      wificConfigSTA(IP, gateway, subnet);
    }
  }

  DEBUG_PRINT("Configuracion de red= " + readMemFlash("config", "config"));

  // Configuracion del servidor web

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Aqui mi ESP32"); });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {}