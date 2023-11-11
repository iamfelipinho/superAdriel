//Pisca Led com pulso
const int led_pin = 23;
//constante inteiro led_pin = pino 23 esp32
void setup() {
  //a funcao de configuracao e executada uma vez quando
  // voce pressiona reset ou liga a placa
  pinMode(led_pin, OUTPUT);

}

void loop() {
 //a funcao de loop e executada repeditamente para sempre
 digitalWrite(led_pin, HIGH);
 delay(1000);
 digitalWrite(led_pin, LOW);
 delay(1000);

}
