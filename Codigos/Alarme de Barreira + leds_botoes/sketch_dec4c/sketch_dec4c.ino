// Definição dos pinos
const int buzzerPin = 32; // Pino para o buzzer (Piezo)
const int ldrPin = 33; // Pino para o LDR (Sensor de Luz)
const int laserPin = 23; // Pino para o laser

// Variáveis para armazenar valores
int ldrValue = 0; // Armazena o valor lido pelo LDR

// Variáveis para controle de tons
int toneVal = 0;
float sinVal;

// Definição dos pinos dos botões e LEDs
const int buttonPins[] = {19, 18, 5, 17}; // Pinos dos 4 botões
const int ledPins[] = {13, 12, 26, 27}; // Pinos dos 4 LEDs

// Variáveis para controle dos botões e LEDs
int buttonStates[] = {LOW, LOW, LOW, LOW}; // Estados atuais dos botões
int lastButtonStates[] = {LOW, LOW, LOW, LOW}; // Estados anteriores dos botões
bool ledOn[] = {false, false, false, false}; // Estado dos LEDs

void setup() {
    Serial.begin(9600); // Inicializa a comunicação serial

    pinMode(buzzerPin, OUTPUT); // Configura o pino do buzzer como saída
    pinMode(laserPin, OUTPUT); // Configura o pino do laser como saída
    digitalWrite(laserPin, HIGH); // Liga o laser ao iniciar o Arduino

    // Configuração dos pinos dos botões como INPUT_PULLUP e LEDs como saída
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW); // Inicializa os LEDs como desligados
    }
}

void loop() {
    ldrValue = analogRead(ldrPin); // Lê o valor do LDR

    // Se a luminosidade for baixa
    if (ldrValue <= 800) {
        sirene(); // Ativa a função para tocar a sirene
        delay(25);
        noTone(buzzerPin); // Interrompe o som do buzzer
    }

    // Verifica o estado dos botões e controla os LEDs
    for (int i = 0; i < 4; i++) {
        buttonStates[i] = digitalRead(buttonPins[i]); // Lê o estado atual do botão

        // Se o botão é pressionado (passou de LOW para HIGH)
        if (buttonStates[i] == HIGH && lastButtonStates[i] == LOW) {
            if (!ledOn[i]) {
                digitalWrite(ledPins[i], HIGH); // Liga o LED
                ledOn[i] = true;
            } else {
                digitalWrite(ledPins[i], LOW); // Desliga o LED
                ledOn[i] = false;
            }
        }

        lastButtonStates[i] = buttonStates[i]; // Atualiza o estado anterior do botão
    }

    // Exibe o valor do sensor no monitor serial
    Serial.print("Valor lido no sensor: ");
    Serial.println(ldrValue);
    delay(50);
}

// Função para tocar a sirene
void sirene() {
    for (int k = 0; k < 5; k++) {
        for (int x = 0; x < 180; x++) {
            sinVal = (sin(x * (3.1412 / 180))); // Cálculo da função seno
            toneVal = 2000 + (int(sinVal * 100)); // Geração de frequência
            tone(buzzerPin, toneVal); // Toca o tom no buzzer
            delay(2); // Atraso para geração do próximo tom
        }
    }
}