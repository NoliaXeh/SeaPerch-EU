// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// And AccelStepper with AFMotor support (https://github.com/adafruit/AccelStepper)
// Public domain!

#include <AFMotor.h>
#include <Scheduler.h>


AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);


template <AF_DCMotor Motor, int speed>
void setup_motor()
{
   Motor.setSpeed(speed);
}

template <AF_DCMotor Motor, int for_ms>
void loop_motor()
{
    Motor.run(FORWARD);
    delay(for_ms);
    Motor.run(RELEASE);
    delay(1000);
}

void setup()
{
   //Serial.begin(9600);           // set up Serial library at 9600 bps
   //Serial.println("Motor test!");

   Scheduler.start(setup_motor<motor1, 5000>, loop_motor<motor1, 150>, 64);
   Scheduler.start(setup_motor<motor2, 5000>, loop_motor<motor2, 150>, 64);
   Scheduler.start(setup_motor<motor3, 5000>, loop_motor<motor3, 150>, 64);
}

void loop()
{
    yield();
}
