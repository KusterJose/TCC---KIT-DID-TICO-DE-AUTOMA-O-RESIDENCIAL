// Definição dos pinos para os componentes
const int buzzerPin = 32; // Piezo no pino 7
const int ldrPin = 33; // LDR no pino analógico 0
const int laserPin = 23;
const int pirPin = 21; // PIR (Sensor de Movimento) no pino 21
const int motionLedPin = 14; // LED de indicação de movimento no pino 14

// Variáveis para armazenar valores
int ldrValue = 0; // Valor lido do LDR
int toneVal = 0; // Valor para controle do tom no buzzer
float sinVal; // Valor para a função seno

// Variáveis para controle dos botões e LEDs
const int buttonPins[] = {19, 18, 5, 17}; // Pinos dos 4 botões
const int ledPins[] = {13, 12, 26, 27}; // Pinos dos 4 LEDs
int buttonStates[] = {LOW, LOW, LOW, LOW}; // Estados atuais dos botões
int lastButtonStates[] = {LOW, LOW, LOW, LOW}; // Estados anteriores dos botões
bool ledOn[] = {false, false, false, false}; // Estado dos LEDs

int pirState = 0; // Variável para armazenar o estado do PIR

void setup() {
    Serial.begin(9600); // Inicialização do monitor serial

    pinMode(buzzerPin, OUTPUT);
    pinMode(laserPin, OUTPUT);
    digitalWrite(laserPin, HIGH); // Liga o laser ao iniciar o Arduino

    // Configuração dos pinos dos botões como INPUT_PULLUP e LEDs como saída
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW); // Inicializa os LEDs como desligados
    }

    pinMode(pirPin, INPUT);
    pinMode(motionLedPin, OUTPUT);
}

void loop() {
    ldrValue = analogRead(ldrPin); // Lê o valor do LDR

    if (ldrValue <= 800) {
        sirene();
        delay(25);
        noTone(buzzerPin);
    }

    // Verifica o estado dos botões e controla os LEDs correspondentes
    for (int i = 0; i < 4; i++) {
        buttonStates[i] = digitalRead(buttonPins[i]);

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

    pirState = digitalRead(pirPin); // Lê o estado do PIR
    Serial.println(pirState); // Exibe o estado do PIR no monitor serial

    // Se o PIR detectar movimento, acende o LED de movimento por 5 segundos
    if (pirState == HIGH) {
        digitalWrite(motionLedPin, HIGH);
        delay(5000);
    } else {
        digitalWrite(motionLedPin, LOW); // Desliga o LED de movimento
    }

    // Exibe o valor do sensor LDR no monitor serial
    Serial.print("Valor lido no sensor: ");
    Serial.println(ldrValue);
    delay(50);
}

// Função para tocar a sirene
void sirene() {
    for (int k = 0; k < 5; k++) {
        for (int x = 0; x < 180; x++) {
            sinVal = (sin(x * (3.1412 / 180))); // Calcula o valor da função seno
            toneVal = 2000 + (int(sinVal * 100)); // Gera uma frequência para o tom
            tone(buzzerPin, toneVal); // Toca o tom no buzzer
            delay(2); // Atraso para gerar o próximo tom
        }
    }
}