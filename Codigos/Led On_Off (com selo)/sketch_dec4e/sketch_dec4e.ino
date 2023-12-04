// Definição dos pinos para o botão e LED
const int buttonPin = 19; // Pino do botão
const int ledPin = 13; // Pino do LED

// Variáveis para controlar o estado do botão, LED e sua última leitura
int buttonState = LOW;
int lastButtonState = LOW;
bool ledOn = false;

void setup() {
  Serial.begin(115200); // Inicialização da comunicação serial
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
}

void loop() {
  buttonState = digitalRead(buttonPin); // Lê o estado atual do botão

  if (buttonState == HIGH && lastButtonState == LOW) {
    // Se o botão foi pressionado uma vez
    if (!ledOn) {
      digitalWrite(ledPin, HIGH); // Liga o LED se estiver apagado
      ledOn = true;
    } else {
      digitalWrite(ledPin, LOW); // Desliga o LED se estiver ligado
      ledOn = false;
    }
  }

  lastButtonState = buttonState; // Atualiza o estado anterior do botão para a próxima iteração
}