#ifndef connections_h
#define connections_h

#include <WiFi.h>
#include <PubSubClient.h>

const char* mqtt_server = "sochoag.ga";
const char* mqtt_username = "glove-esp32";
const char* mqtt_password = "10101011";

//Clientes
WiFiClient esp32Client;
PubSubClient client(esp32Client);



void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String msg;

  for (int i = 0; i < length; i++) 
  {
    msg = msg + (char)payload[i];
  }

  if(strcmp(topic,"glove/fingers/acts")==0)
  {
    Serial.println("Cambiando periodo de publicacion");
    if(msg.toInt() > 100)
    {
      Serial.println("Periodo de publicacion: "+msg);
      period = msg.toInt();
    }
  }
}

void initMQTT() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "Glove-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.publish("glove/finger/1", "Hola desde ESP32");
      client.subscribe("glove/fingers/acts");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loopMQTT() 
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void publishMQTT(String topic,String message)
{
  client.publish(topic.c_str(), message.c_str());
  Serial.println("Pubicado con exito");
}
#endif