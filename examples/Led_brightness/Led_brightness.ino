//пример управления яркостью светодиода с помощью джостикаю

#include "UnoJoystick.h"

// Создаем объект для работы с джойстиком
JoystickHandler joystick;

void setup() {
  Serial.begin(9600);
  joystick.begin();
  pinMode(9, OUTPUT); // Пин для ШИМ-управления светодиодом
  Serial.println("Калибровка оси X. Посмотрите на значения в мониторе порта.");
}

void loop() {
  // Читаем текущее состояние
  JoystickHandler::JoystickState state = joystick.readJoystick();

  // Выводим значение оси X для анализа (нормальное значение покоя ~512)
  Serial.print("X Axis Raw Value: ");
  Serial.println(state.x);

  // Масштабируем значение с аналогового пина (0-1023) в диапазон ШИМ (0-255)
  // Функция map() делает это автоматически.
  int brightness = map(state.x, 0, 1023, 0, 255);

  // Устанавливаем яркость светодиода
  analogWrite(9, brightness);

  delay(50); // Небольшая задержка для стабильности
}