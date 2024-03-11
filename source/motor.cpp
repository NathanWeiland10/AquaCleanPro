#include "motor.hpp"
#include "Arduino.h"

/// @brief Default constructor for a motor controlled by the L298N
Motor::Motor(){

}

/// @brief Default constructor for a motor controlled by the L298N
/// @param pinNumE Pin E of the motor
/// @param pinNumM Pin M of the motor
Motor::Motor(int pinNumE, int pinNumM){
  pinE = pinNumE;
  pinM = pinNumM;

  pinMode(pinE, OUTPUT);
  pinMode(pinM, OUTPUT);
}

/// @brief Stops the motor
void Motor::stop(){
  digitalWrite(pinE, LOW);
  digitalWrite(pinM, LOW);
}

/// @brief Turns the motor forward at full speed
void Motor::turnForward(){
  digitalWrite(pinE, HIGH);
  digitalWrite(pinM, LOW);
}

/// @brief Turns the motor backwards at full speed
void Motor::turnBackward(){
  digitalWrite(pinE, HIGH);
  digitalWrite(pinM, HIGH);
}