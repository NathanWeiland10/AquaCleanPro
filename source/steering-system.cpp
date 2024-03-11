#include "steering-system.hpp"
#include "motor.hpp"

/// @brief Default constructor of the steering system
/// @param _leftMotor Reference to the left motor
/// @param _rightMotor Reference to the right motor
SteeringSystem::SteeringSystem(Motor _leftMotor, Motor _rightMotor){
  leftMotor = _leftMotor;
  rightMotor = _rightMotor;
  state = STOPPED;
}

/// @brief Stops the movement of the craft
void SteeringSystem::stop(){
  state = STOPPED;
  leftMotor.stop();
  rightMotor.stop();
}

/// @brief Makes the craft go forward
void SteeringSystem::go(){
  state = FORWARD;
  leftMotor.turnForward();
  rightMotor.turnForward();
}

/// @brief Turns the craft right
void SteeringSystem::turnRight(){
  state = TURNING_RIGHT;
  turnTimer = TURN_TIME;
  leftMotor.turnForward();
  rightMotor.turnBackward();
}

/// @brief Turns the craft left
void SteeringSystem::turnLeft(){
  state = TURNING_LEFT;
  turnTimer = TURN_TIME;
  leftMotor.turnBackward();
  rightMotor.turnForward();
}

/// @brief Updates the steering timer
void SteeringSystem::update(){
  // Decrement turnTimer if turning
  if (state == TURNING_LEFT || state == TURNING_RIGHT)
  {
    turnTimer -= 1;

    // Reset to forward motion when turnTimer is 0
    if (turnTimer == 0){
      go();
    }
  }
}