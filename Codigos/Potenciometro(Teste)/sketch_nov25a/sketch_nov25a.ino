const int potenciometroPin = 33; // Pino de entrada do potenciômetro

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  int valorPotenciometro = analogRead(potenciometroPin); // Lê o valor do potenciômetro
  Serial.print("Valor do Potenciômetro: ");
  Serial.println(valorPotenciometro); // Exibe o valor lido do potenciômetro no monitor serial
  delay(100); // Pequeno atraso para evitar leituras muito rápidas e instáveis
}