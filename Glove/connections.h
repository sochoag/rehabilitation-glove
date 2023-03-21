#ifndef connections_h
#define connections_h

#include <WiFi.h>
#include <PubSubClient.h>

// Clientes
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void initWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
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
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}

void reconnect()
{
  while (!mqttClient.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "glove-esp32-";
    clientId += String(random(0xffff), HEX);
    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("connected");
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

void connect(){
  initWifi();
  initMQTT();
}

void disconnect(){
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
#endif