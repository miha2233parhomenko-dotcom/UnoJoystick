//пример управления серводвигателя с помощью джостика.

#include <Servo.h> // Подключаем стандартную библиотеку для сервоприводов
#include "UnoJoystick.h"

// Создаем объекты
JoystickHandler joystick;
Servo myServo; 

void setup() {
  Serial.begin(9600);
  joystick.begin();
  
  // Привязываем сервопривод к пину 3 и устанавливаем в центральное положение (90 градусов)
  myServo.attach(3);
  myServo.write(90);
}

void loop() {
  JoystickHandler::JoystickState state = joystick.readJoystick();

  // Масштабируем значение оси X (0-1023) в угол поворота (0-180 градусов)
  int angle = map(state.x, 0, 1023, 0, 180);
  
  // Управляем сервоприводом
  myServo.write(angle);

  // Выводим информацию для отладки
  Serial.print("X: ");
  Serial.print(state.x);
  Serial.print(" | Angle: ");
  Serial.println(angle);

  delay(20); // Сервоприводы не любят слишком частых обновлений, но и большая задержка даст "рваный" ход
}