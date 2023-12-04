// Declaração dos pinos
const int buzzerPin = 32; // Piezo no pino 7
const int ldrPin = 33; // LDR no pino analógico 0
const int laserPin = 23;

// Variáveis para armazenar valores do LDR e controle do tom
int ldrValue = 0; // Valor lido do LDR
int toneVal = 0;
int toneAdjustment = 2000; // Ajuste de tom
float sinVal;

void setup() {
    Serial.begin(9600); // Inicialização do monitor serial
    pinMode(buzzerPin, OUTPUT); // Define o pino do buzzer como saída
    pinMode(laserPin, OUTPUT); // Define o pino do laser como saída
    digitalWrite(laserPin, HIGH); // Liga o laser ao iniciar o Arduino
}

void loop() {
    ldrValue = analogRead(ldrPin); // Lê o valor do LDR

    // Se a luminosidade for baixa
    if (ldrValue <= 800) {
        // Ativa a sirene
        sirene();
        delay(25); // Espera um pouco
        noTone(buzzerPin); // Interrompe o tom
    }

    // Exibe o valor do sensor no monitor serial
    Serial.print("Valor lido no sensor: ");
    Serial.println(ldrValue);
    delay(50);
}

// Função para acionar a sirene
void sirene() {
    // Toca 5 ciclos
    for (int k = 0; k < 5; k++) {
        for (int x = 0; x < 180; x++) {
            // Converte graus em radianos
            sinVal = (sin(x * (3.1412 / 180)));
            // Gera uma frequência
            toneVal = 2000 + (int(sinVal * 100));
            // Toca o valor no buzzer
            tone(buzzerPin, toneVal);
            // Atraso de 2ms e gera novo tom
            delay(2);
        }
    }
}