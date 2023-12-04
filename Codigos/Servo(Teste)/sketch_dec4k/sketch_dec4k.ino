#include <ESP32Servo.h>

Servo myservo; // Cria um objeto servo para controlar um servo motor
// No ESP32, até 16 objetos servo podem ser criados

int pos = 0; // Variável para armazenar a posição do servo

// Pinos PWM recomendados no ESP32 incluem 2, 4, 12-19, 21-23, 25-27, 32-33
int servoPin = 25;

void setup() {
  // Permite a alocação de todos os timers necessários para os servos
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo.setPeriodHertz(50); // Configura o servo para 50Hz padrão
  myservo.attach(servoPin, 500, 2400); // Conecta o servo no pino 18 ao objeto servo
                                       // usando min/max padrão de 1000us e 2000us
                                       // diferentes servos podem exigir configurações diferentes
                                       // para um movimento preciso de 0 a 180 graus
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // Move o servo de 0 graus a 180 graus
    myservo.write(pos); // Define a posição do servo para o valor na variável 'pos'
    delay(15); // Aguarda 15ms para o servo atingir a posição
  }

  for (pos = 180; pos >= 0; pos -= 1) { // Move o servo de 180 graus a 0 graus
    myservo.write(pos); // Define a posição do servo para o valor na variável 'pos'
    delay(15); // Aguarda 15ms para o servo atingir a posição
  }
}