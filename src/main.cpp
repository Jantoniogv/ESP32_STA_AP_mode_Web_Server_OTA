#include <Arduino.h>

#include "config.h"
#include "wifiConnect.h"
#include "serverFunctions.h"

#define DEBUG
#include "debugUtils.h"

void setup()
{
  // Borra todas las claves del espacio de nombres en memoria
  // eraseFlash("config");

  // Inicializa el objeto con la variables de configuracion
  Config configData;

  /*  // Tarea a implementar en caso necesario
   TaskHandle_t handleMqtt = NULL;

   xTaskCreatePinnedToCore(
       taskMqtt,
       "taskMqtt",
       16000,
       NULL,
       1,
       &handleMqtt,
       1); */

  // Inicializa la conexion serial
  Serial.begin(115200);

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

  // Configura el servidor web
  serverHandlers();

  // Inicia ElegantOTA
  AsyncElegantOTA.begin(&server);

  // Inicia el servidor
  server.begin();

  DEBUG_PRINT("Servidor HTTP iniciado...");

  DEBUG_PRINT("Configuracion de red= " + readMemFlash("config", "config"));
}

void loop()
{
  /* Serial.println("Estoy aqui en el loop");

  vTaskDelay(pdMS_TO_TICKS(10)); */
}