#include "motor.hpp"
#define TURN_TIME 10

class SteeringSystem{
    public:
        SteeringSystem(Motor _leftMotor, Motor _rightMotor);

        void stop();

        void go();

        void turnRight();

        void turnLeft();

        void update();

    enum State{
        STOPPED,
        FORWARD,
        TURNING_LEFT,
        TURNING_RIGHT
    };

    private:
        Motor leftMotor;
        Motor rightMotor;
        int turnTimer;
        State state;
};