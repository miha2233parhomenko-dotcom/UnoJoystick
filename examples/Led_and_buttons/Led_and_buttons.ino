#include <UnoJoystick.h>

JoystickHandler joystick;
const int LED_PIN = 9;

void setup() {
  joystick.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Создаем переменную для хранения состояния
  JoystickHandler::JoystickState state;
  
  // Заполняем переменную текущими данными с джойстика
  state = joystick.readJoystick();
  
  // Проверяем поле buttonPressed в полученной структуре
  if (state.buttonPressed) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}