#include "UnoJoystick.h"
#include <Arduino.h>

// --- ОПРЕДЕЛЕНИЕ СТАТИЧЕСКОГО МАССИВА ---
// Инициализация массива с пинами кнопок.
const int JoystickHandler::buttonPins[NUM_BUTTONS] = {
    PIN_BUTTON_A, PIN_BUTTON_B, PIN_BUTTON_C,
    PIN_BUTTON_D, PIN_BUTTON_E, PIN_BUTTON_F
};

// --- РЕАЛИЗАЦИЯ МЕТОДОВ ---

// Конструктор (может быть пустым)
JoystickHandler::JoystickHandler() {
}

void JoystickHandler::begin() {
    // Настраиваем пины кнопок как входы с подтяжкой к питанию (INPUT_PULLUP)
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
    pinMode(PIN_JOYSTICK_BTN, INPUT_PULLUP);
}

JoystickHandler::JoystickState JoystickHandler::readJoystick() {
    JoystickState state;
    state.x = getXAxis();
    state.y = getYAxis();
    state.buttonPressed = isButtonPressed(PIN_JOYSTICK_BTN);
    state.direction = getDirection(state.x, state.y);
    return state;
}

bool JoystickHandler::isButtonPressed(int buttonPin) {
     // При нажатии кнопка соединяет пин с GND, на нем будет LOW
     return digitalRead(buttonPin) == LOW; 
}

int JoystickHandler::getXAxis() {
     return analogRead(PIN_X_AXIS);
}

int JoystickHandler::getYAxis() {
     return analogRead(PIN_Y_AXIS);
}

// Логика определения направления движения
JoystickHandler::Direction JoystickHandler::getDirection(int x, int y) {
     // Проверка на "мертвую зону" (нейтральное положение)
     if (abs(x - NEUTRAL_VALUE) < DEAD_ZONE && abs(y - NEUTRAL_VALUE) < DEAD_ZONE) {
         return CENTER;
     }
     
     // Определяем смещение по осям (-1, 0, 1)
     int dirX = (x > NEUTRAL_VALUE + DEAD_ZONE) ? 1 : ((x < NEUTRAL_VALUE - DEAD_ZONE) ? -1 : 0);
     int dirY = (y > NEUTRAL_VALUE + DEAD_ZONE) ? 1 : ((y < NEUTRAL_VALUE - DEAD_ZONE) ? -1 : 0);
     
     // Определяем итоговое направление на основе смещения
     if (dirX == 0 && dirY == 1) return UP;
     if (dirX == 1 && dirY == 1) return UP_RIGHT;
     if (dirX == 1 && dirY == 0) return RIGHT;
     if (dirX == 1 && dirY == -1) return DOWN_RIGHT;
     if (dirX == 0 && dirY == -1) return DOWN;
     if (dirX == -1 && dirY == -1) return DOWN_LEFT;
     if (dirX == -1 && dirY == 0) return LEFT;
     if (dirX == -1 && dirY == 1) return UP_LEFT;
     
     return CENTER; 
}