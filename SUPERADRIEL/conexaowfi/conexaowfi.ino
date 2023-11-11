// Inclusão Biblioteca Wifi
#include <WiFi.h>

// Configuração Rede Local 
const char* ssid = "I.O.T_Prof.Michel";
const char* password = "IOT20222";

// Servidor Wifi na Porta 80
WiFiServer server (80);

void setup ()
{
// Configura Comunicação Serial

  Serial.begin(115200); // velocidade da porta
  delay(10);

  // Conectando a uma rede WiFi
  Serial.println();
  Serial.println ();
  Serial.print("Conectando para a rede");
  Serial.println(ssid);

  // Inicializando e validando a rede
  WiFi.begin(ssid, password);

  // aguarda a conexão WiFi
  while (WiFi.status () != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

    // mensagem de Conectado à Rede
  Serial.println("");
  Serial.println("WiFi connected.") ;
  Serial.println("IP address: ");
  Serial.println (WiFi.localIP ());
  Serial.print( "ESP Mac\Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print ("Subnet Mask: ") ;
  Serial.println (WiFi.subnetMask());
  Serial.print("Gateway IP: ") ;
  Serial.println (WiFi.gatewayIP ()) ;
  Serial.print ("DNS: ");
  Serial.println(WiFi.dnsIP());
  server.begin() ;
}

void loop()
{
  //sem ação
}