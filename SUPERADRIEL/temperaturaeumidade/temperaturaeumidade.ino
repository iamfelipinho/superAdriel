#include <PubSubClient.h>
#include <WiFi.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 4
#define DHTTYPE DHT22
#define MSG_BUFFER_SIZE (50)
const char* ssid = "Galaxy21";
const char* password = "IOT123456";
const char* mqtt_server = "broker.mqtt-dashboard.com";
char msg[MSG_BUFFER_SIZE];
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
unsigned long lastMg = 0;
int value = 0;
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
  delay(10);
  Serial.println("");
  Serial.print("Conectando com");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Ip: ");
  Serial.println(WiFi.localIP());
}
void reconnect()
{
  while(!client.connected()){
    Serial.print("Aguardando conexão MQTT...");
    String clientId = "ESP32Client";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())){
      Serial.println("Conectado");
      client.subscribe("casa/publisher");
    }
    else{
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println("Tente novamente em 5s");
      delay(500);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  setup_wifi();
  client.setServer(mqtt_server,1883);
  Serial.begin(115200);
  dht.begin();
  Serial.println(F("SENSOR DHT22"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("---------------------"));
  Serial.println(F("Temperature"));
  Serial.print(F("Sensor: "));
  Serial.println(sensor.name);
  Serial.print(F("Valor maximo: "));
  Serial.print(sensor.max_value);
  Serial.println(F("°C"));
  Serial.print(F("Valor mínimo: "));
  Serial.print(sensor.min_value);
  Serial.println(F("°C"));
  Serial.print(F("Resolução: "));
  Serial.print(sensor.resolution);
  Serial.println(F("°C"));
  Serial.println(F("---------------------"));
  dht.humidity().getSensor(&sensor);
  Serial.println(F("---------------------"));
  Serial.println(F("Umidade"));
  Serial.print(F("Sensor: "));
  Serial.println(sensor.name);
  Serial.print(F("Valor máximo: "));
  Serial.print(sensor.max_value);
  Serial.println(F("%"));
  Serial.print(F("Valor minimo"));
  Serial.print(sensor.min_value);
  Serial.println(F("%"));
  Serial.print(F("Resolução: "));
  Serial.print(sensor.resolution);
  Serial.println(F("%"));
  Serial.println(F("---------------------"));
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if(isnan(event.temperature)){
    Serial.println(F("Erro na leitura"));
  }
  else{
    Serial.print(F("Temperatura: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    sprintf(msg,"%f",event.temperature);
    client.publish("Nycolas/temp", msg);
  }
  dht.humidity().getEvent(&event);
  Serial.print(event.relative_humidity);
  if(isnan(event.relative_humidity)){
    Serial.println(F("Erro na leitura da umidade!"));
  }
  else{
    Serial.print(F("Umidade: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    sprintf(msg,"%f",event.relative_humidity);
    client.publish("Nycolas/umid", msg);
  }
  if(!client.connected()){
    reconnect();
  }
  client.loop();
}
