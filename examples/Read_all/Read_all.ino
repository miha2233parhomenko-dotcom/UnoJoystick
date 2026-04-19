
#include "UnoJoystick.h"

JoystickHandler joystick;
JoystickHandler::JoystickState state;

void setup() {
  Serial.begin(9600);
  joystick.begin(); 
}

void loop() {
  state = joystick.readJoystick();
  
  Serial.print("X: ");
  Serial.print(state.x);
  Serial.print(" | Y: ");
  Serial.print(state.y);
  
  Serial.print(" | Button: ");
  Serial.print(state.buttonPressed ? "Pressed" : "Released");
  
  Serial.print(" | Dir: ");
  Serial.println(state.direction); 
  
  delay(200); 
} 
