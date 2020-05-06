#include "DHT.h"

#define DHTPIN 13 // PINO DE DADOS DO NODEMCU
#define DHTTYPE DHT11 // MODELO DO SENSOR

DHT dht(DHTPIN, DHTTYPE); // INICIALIZA O SENSOR DHT11

int ledVerde = 4; // D2 - (LED)
int ledVermelho = 5; // D1 - (LED)

void setup() {
  Serial.begin(9800);
  
  dht.begin();
  
  delay(10);

  pinMode(ledVerde, OUTPUT); // CONFIGURA COMO PINO DE SAIDA 
  pinMode(ledVermelho, OUTPUT); // CONFIGURA COMO PINO DE SAIDA 
  
  Serial.println("Iniciando..");
}

void loop() {
  
  float u = dht.readHumidity(); // CAPTURA A UMIDADE
  float t = dht.readTemperature(); // CAPTURA A TEMPERATURA

  if(isnan(t) || isnan(u)){
    Serial.println("Falha de leitura");
    }
    else{
      // IMPRIME VALORES
      Serial.print("Umidade: ");
      Serial.println(u);
      Serial.print("Temperatura: ");
      Serial.println(t);
      
      if(t >= 25){ // SE A TEMPERATURA FOR MAIOR QUE 23º
        digitalWrite(ledVerde, HIGH); // ACENDE VERDE
        digitalWrite(ledVermelho, LOW); // APAGA VERMELHO
      }
      else{
        digitalWrite(ledVerde, LOW); // APAGA VERDE
        digitalWrite(ledVermelho, HIGH); // ACENDE VERMELHO
      }
    }

  // DELAY DE 5 SEGUNDOS ATÉ A NOVA LEITURA
  delay(5000);
}

