#ifndef connections_h
#define connections_h

#include <WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// Configuramos el cliente NTP para obtener la hora desde un servidor NTP

// Definimos una constante con la cantidad de segundos en 5 horas
const int GMT_OFFSET = 18000;

// Clientes
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void reconnectWifi()
{
  isConnected = false;
  oledWifi();
  delay(1000);
}

void initWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    reconnectWifi();
  }
  isConnected = true;
  Serial.println(WiFi.localIP());
  timeClient.begin();
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String msg;

  for (int i = 0; i < length; i++)
  {
    msg = msg + (char)payload[i];
  }

  if (strcmp(topic, "glove/fingers/acts") == 0)
  {
    Serial.println("Cambiando periodo de publicacion");
    if (msg.toInt() > 100)
    {
      Serial.println("Periodo de publicacion: " + msg);
      period = msg.toInt();
    }
  }
}

void initMQTT()
{
  mqttClient.setServer(mqtt_server.c_str(), 1883);
  mqttClient.setCallback(callback);
}

void reconnect()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    reconnectWifi();
  }
  isConnected = true;
  while (!mqttClient.connected())
  {
    oledMQTT();
    String clientId = "glove-esp32-";
    clientId += String(random(0xffff), HEX);
    if (mqttClient.connect(clientId.c_str(), mqtt_username.c_str(), mqtt_password.c_str()))
    {
      mqttClient.subscribe("glove/fingers/acts");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void connect()
{
  initWifi();
  initMQTT();
}

void disconnect()
{
  mqttClient.disconnect();
  WiFi.disconnect();
}

void loopMQTT()
{
  if (!mqttClient.connected())
  {
    reconnect();
  }
  mqttClient.loop();
}

void publishMQTT(String topic, String message)
{
  mqttClient.publish(topic.c_str(), message.c_str());
  Serial.println("Publicado con exito: " + message);
}

void getTime()
{
  timeClient.update();
  time_t hora_unix = timeClient.getEpochTime();
  hora_unix -= GMT_OFFSET;
  struct tm *tm_struct = localtime(&hora_unix);
  sprintf(hora_actual, "%02d:%02d", tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);
}
#endif