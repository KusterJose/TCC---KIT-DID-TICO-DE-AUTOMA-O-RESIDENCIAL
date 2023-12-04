#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Nextion.h>

// Declaração dos objetos para os componentes Nextion
NexProgressBar j0 = NexProgressBar(0, 7, "j0");
NexText txt_temp = NexText(0, 6, "t0");
NexText txt_humi = NexText(0, 3, "t2");

// Definição do pino e tipo do sensor DHT
#define DHTPIN 36
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variáveis para armazenar os valores de temperatura e percentual de temperatura
int temp = 0;
int temp_perc = 0;
char buffer[100] = {0};
char buffer2[100] = {0};

void setup() {
  nexInit(); // Inicialização da comunicação com o Nextion Display
}

void loop() {
  int temp = dht.readTemperature(); // Lê a temperatura do sensor
  int humi = dht.readHumidity(); // Lê a umidade do sensor

  // Limpa os buffers de caracteres
  memset(buffer, 0, sizeof(buffer));
  memset(buffer2, 0, sizeof(buffer2));

  // Converte o valor da temperatura para uma string
  itoa(temp, buffer, 10);

  // Conversão da temperatura para percentual (0 a 50 para 0 a 100)
  temp_perc = map(temp, 0, 50, 0, 100);

  // Define o valor da barra de progresso no Nextion Display com base no percentual da temperatura
  j0.setValue(temp_perc);

  // Atualiza o texto do Nextion Display com a temperatura
  txt_temp.setText(buffer);

  // Atualiza o texto do Nextion Display com a umidade (buffer2 está vazio, não atualiza com umidade)

  delay(1000); // Aguarda 1 segundo entre as leituras (ajuste conforme necessário)
}