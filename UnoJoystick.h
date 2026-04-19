#ifndef UNOJOYSTICK_H
#define UNOJOYSTICK_H

// --- НАСТРОЙКИ ПИНОВ ---
// Эти дефайны можно вынести в основной скетч, если нужно
#define PIN_BUTTON_A 2
#define PIN_BUTTON_B 3
#define PIN_BUTTON_C 4
#define PIN_BUTTON_D 5
#define PIN_BUTTON_E 6
#define PIN_BUTTON_F 7
#define PIN_JOYSTICK_BTN 8
#define PIN_Y_AXIS A0
#define PIN_X_AXIS A1

class JoystickHandler {
public:
    // Перечисление для 8 направлений + центр
    enum Direction {
        CENTER,
        UP,
        UP_RIGHT,
        RIGHT,
        DOWN_RIGHT,
        DOWN,
        DOWN_LEFT,
        LEFT,
        UP_LEFT
    };

    // Структура для хранения состояния
    struct JoystickState {
        int x;
        int y;
        bool buttonPressed;
        Direction direction;
    };

    // Конструктор (объявление)
    JoystickHandler();

    // Методы (объявления)
    void begin(); // Инициализация пинов (вместо setup)
    JoystickState readJoystick();
    bool isButtonPressed(int buttonPin);
    int getXAxis();
    int getYAxis();
    
private:
    // Объявление статического массива и его размера
    static const int NUM_BUTTONS = 6;
    static const int buttonPins[NUM_BUTTONS];

    // Константы для логики (имена изменены, чтобы избежать конфликта)
    const int NEUTRAL_VALUE = 512;
    const int DEAD_ZONE = 50;
    
    // Приватный метод для вычисления направления
    Direction getDirection(int x, int y);
};

#endif // UNOJOYSTICK_H