#define entradaDigital 33
//#define entradaAnalogica 35

bool dSensor;
//int aSensor;

void setup() {
  Serial.begin(9600); // Inicialização da comunicação serial
  
  pinMode(entradaDigital, INPUT); // Configura o pino como entrada digital
}

void loop() {
  dSensor = digitalRead(entradaDigital); // Lê o valor da entrada digital
  //aSensor = analogRead(entradaAnalogica); // Lê o valor da entrada analógica (comentada)

  Serial.print("Leitura entrada digital: ");
  Serial.println(dSensor); // Exibe o valor da entrada digital lida
  
  //Serial.print("Leitura entrada analógica: ");
  //Serial.println(aSensor); // Exibe o valor da entrada analógica lida (comentada)
  
  Serial.println(); // Imprime uma linha em branco para melhor legibilidade
  
  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}