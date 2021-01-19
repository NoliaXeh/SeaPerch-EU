#include <AFMotor.h>

#define JOYSTICK_ERROR 5

const int UP    = A0;
const int LEFT  = A2;
const int DOWN  = A3;
const int RIGHT = A1;
const int JOY_Y = A4;
const int JOY_X = A5;

bool up = false;
bool down = false;
bool left = false;
bool right = false;
int direction = RELEASE;
int speed = 0;
int lval = 0;
int rval = 0;

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);


auto motor_left = motor1;
auto motor_right = motor2;
auto motor_up = motor3;

void setup()
{
  Serial.begin(115200);
  motor_left.setSpeed(0);
  motor_right.setSpeed(0);
  motor_up.setSpeed(255);
}


void readInputs()
{
    up = digitalRead(UP);
    down = digitalRead(DOWN);
    left = digitalRead(LEFT);
    right = digitalRead(RIGHT);

    double x = analogRead(JOY_X) - 512;
    double y = analogRead(JOY_Y) - 512;

    if (y > JOYSTICK_ERROR)
    {
        direction = FORWARD;
        speed = max(150, y/2);
    }
    else if (y > -JOYSTICK_ERROR)
    {
        direction = RELEASE;
        speed = 0;
    }
    else // y < -JOYSTICK_ERROR
    {
        direction = BACKWARD;
        speed = max(150, (-y)/2);
    }
    rval = 155 + 50 + ((x/512.0)*50.0);
    lval = 155 + 50 + ((-x/512.0)*50.0);
}

void debugInputs()
{
    Serial.print("up: ");Serial.print(up);
    Serial.print(", down: ");Serial.print(down);
    Serial.print(", left: ");Serial.print(left);
    Serial.print(", right: ");Serial.print(right);
    Serial.print(", rval: ");Serial.print(rval);
    Serial.print(", lval: ");Serial.print(lval);
    Serial.print(", dir: ");Serial.print(direction);
    Serial.print(", speed: ");Serial.print(speed);
    Serial.print("\n"); 
}

void updateMotors()
{
    motor_right.setSpeed(rval);
    motor_left.setSpeed(lval);
    motor_right.run(direction);
    motor_left.run(direction);

    if (up)
        motor_up.run(FORWARD);
    else if (down)
        motor_up.run(BACKWARD);
    else
        motor_up.run(RELEASE);
}

void loop()
{
    readInputs();
    debugInputs();
    updateMotors();
    delay(10);
}
