
#include "config.h"
#define LED_PIN 2

AdafruitIO_Feed *digital = io.feed("saida");

void setup() // configurações 
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

while(! Serial);

Serial.print ("Conectando com Adafruit IO");
io.connect();

digital->onMessage(handleMessage);

while(io.status() < AIO_CONNECTED)
{
  Serial.print(".");
  delay(500);
}
Serial.println();
Serial.println(io.statusText());
digital->get();
}

void loop()//laco infinito
{
  io.run();
}

void handleMessage(AdafruitIO_Data *data)
{
  Serial.print("recebido <- ");

if(data->toPinLevel() == HIGH)
  Serial.println("HIGH");
else
  Serial.println("LOW");
digitalWrite(LED_PIN, data->toPinLevel());

}
