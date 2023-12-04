// Declaração dos pinos dos botões e LEDs
const int buttonPins[] = {19, 18, 5, 17}; // Pinos dos 4 botões
const int ledPins[] = {13, 12, 26, 27}; // Pinos dos 4 LEDs

// Arrays para armazenar estados dos botões e LEDs
int buttonStates[] = {LOW, LOW, LOW, LOW}; // Estados atuais dos botões
int lastButtonStates[] = {LOW, LOW, LOW, LOW}; // Estados anteriores dos botões
bool ledOn[] = {false, false, false, false}; // Estado dos LEDs

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial

  // Configuração dos pinos
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Configura os pinos dos botões como INPUT_PULLUP
    pinMode(ledPins[i], OUTPUT); // Configura os pinos dos LEDs como OUTPUT
    digitalWrite(ledPins[i], LOW); // Inicializa os LEDs como desligados
  }
}

void loop() {
  // Verifica o estado dos botões
  for (int i = 0; i < 4; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]); // Lê o estado atual do botão

    // Verifica se o botão foi pressionado (passou de LOW para HIGH)
    if (buttonStates[i] == HIGH && lastButtonStates[i] == LOW) {
      if (!ledOn[i]) { // Se o LED estiver desligado
        digitalWrite(ledPins[i], HIGH); // Liga o LED
        ledOn[i] = true; // Atualiza o estado do LED
      } else { // Se o LED estiver ligado
        digitalWrite(ledPins[i], LOW); // Desliga o LED
        ledOn[i] = false; // Atualiza o estado do LED
      }
    }

    lastButtonStates[i] = buttonStates[i]; // Atualiza o estado anterior do botão
  }
}