#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 13 // PINO DE DADOS
#define DHTTYPE DHT11 // MODELO DO SENSOR

DHT dht(DHTPIN, DHTTYPE); // INIT

const char* ssid = "Fast Net Simplicio";
const char* senha = "52872211";

int ledVerde = 4; // D2
int ledVermelho = 5; // D1

WiFiServer server(80);

void setup() {
  Serial.begin(9800);
  dht.begin();
  delay(10);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  
  Serial.print("Conectando a rede:");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");

  server.begin();
  Serial.println("Servidor iniciado");

  Serial.print("Use esta URL: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient cliente = server.available();
  if(!cliente){
    return;
  }
  
  Serial.println("Novo cliente");
  while(!cliente.available()){
    delay(1);
  }
  String requisicao = cliente.readStringUntil('\r');
  Serial.println(requisicao);
  cliente.flush();

  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type:text/html");
  cliente.println("");
  cliente.println("<!DOCTYPE HTML>");

  cliente.println("<html>");
  cliente.println("<br><br>");

  float u = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(t) || isnan(u)){
    Serial.println("Falha de leitura");
    }
    else{
      Serial.print("Umidade: ");
      Serial.println(u);
      Serial.print("Temperatura: ");
      Serial.println(t);
      if(t > 24){
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledVermelho, LOW);
        }
        else{
         digitalWrite(ledVerde, LOW);
         digitalWrite(ledVermelho, HIGH);
          }
      cliente.print("Umidade: ");
      cliente.println(u);
      cliente.println("<br><br>");
      cliente.print("Temperatura: ");
      cliente.println(t);
      }
  cliente.println("</html>");
  delay(1);
}

