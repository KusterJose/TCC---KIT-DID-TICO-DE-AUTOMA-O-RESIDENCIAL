// Definição dos pinos para o PIR e LED
const int pirPin = 21; // Pino do sensor PIR
const int ledPin = 14; // Pino do LED

int pirState = 0; // Variável para armazenar o estado do sensor PIR

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  
  pinMode(pirPin, INPUT); // Configura o pino do sensor PIR como entrada
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
}

void loop() {
  pirState = digitalRead(pirPin); // Lê o estado atual do sensor PIR
  Serial.println(pirState); // Exibe o estado do sensor PIR no monitor serial
  
  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH); // Liga o LED se o sensor PIR detectar movimento
    delay(5000); // Mantém o LED aceso por 5 segundos
  } else {
    digitalWrite(ledPin, LOW); // Desliga o LED se nenhum movimento for detectado
  }
}