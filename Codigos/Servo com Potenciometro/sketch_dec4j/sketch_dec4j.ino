#include <ESP32Servo.h>

Servo myservo;  // Cria um objeto servo para controlar um servo motor

// Pinos GPIO possíveis para PWM no ESP32: 0 (usado pelo botão onboard), 2, 4, 5 (usado pelo LED onboard), 12-19, 21-23, 25-27, 32-33 
int servoPin = 25;  // Pino GPIO usado para conectar o controle do servo (saída digital)
// Pinos ADC possíveis no ESP32: 0, 2, 4, 12-15, 32-39; 34-39 são recomendados para entrada analógica
int potPin = 15;    // Pino GPIO usado para conectar o potenciômetro (entrada analógica)
int ADC_Max = 4096; // Este é o valor máximo ADC padrão no ESP32 (largura de 12 bits);
                    // Esta largura pode ser configurada (em código de baixo nível) de 9-12 bits, para um
                    // um intervalo de valores máximos de 512-4096
  
int val;  // Variável para armazenar o valor lido do pino analógico

void setup() {
  // Permitir alocação de todos os timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo.setPeriodHertz(50); // Servo padrão de 50Hz
  myservo.attach(servoPin, 500, 2400); // Conecta o servo no pino 18 ao objeto servo
                                       // usando min/max de 500us e 2400us para servo SG90
                                       // para MG995 servo grande, use 1000us e 2000us,
                                       // que são os padrões, então esta linha poderia ser
                                       // "myservo.attach(servoPin);"
}

void loop() {
  val = analogRead(potPin);          // Lê o valor do potenciômetro (valor entre 0 e 1023)
  val = map(val, 0, ADC_Max, 0, 180); // Escala o valor para usá-lo com o servo (valor entre 0 e 180)
  myservo.write(val);                // Define a posição do servo de acordo com o valor escalado
  delay(200);                        // Aguarda o servo chegar na posição desejada
}