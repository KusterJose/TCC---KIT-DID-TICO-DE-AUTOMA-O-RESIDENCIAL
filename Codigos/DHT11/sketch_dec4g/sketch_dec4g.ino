#include "DHT.h"

#define DHT11PIN 26

DHT dht(DHT11PIN, DHT11); // Criação do objeto DHT utilizando o pino 26 para o DHT11

void setup() {
  Serial.begin(115200); // Inicialização da comunicação serial

  dht.begin(); // Inicialização do sensor DHT
  delay(2000); // Aguarda 2 segundos para estabilização do sensor
}

void loop() {
  float umi = dht.readHumidity(); // Lê a umidade do sensor
  float temp = dht.readTemperature(); // Lê a temperatura do sensor

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("ºC "); // Exibe a temperatura em graus Celsius
  Serial.print("Umidade: ");
  Serial.println(umi); // Exibe a umidade

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}