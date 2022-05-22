#define leftMotor1 11
#define leftMotor2 10
#define leftMotorE 5
#define rightMotor1 13
#define rightMotor2 12
#define rightMotorE 6

void setup()
{
    pinMode(leftMotor1, OUTPUT);
    pinMode(leftMotor2, OUTPUT);
    pinMode(leftMotorE, OUTPUT);
    pinMode(rightMotor1, OUTPUT);
    pinMode(rightMotor2, OUTPUT);
    pinMode(rightMotorE, OUTPUT);

    Serial.begin(9600);
}

void moveStraight(int leftMotorSpeed, int rightMotorSpeed)
{
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    analogWrite(leftMotorE, leftMotorSpeed);

    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotorE, rightMotorSpeed);
}

void turnCCW(int leftMotorSpeed, int rightMotorSpeed)
{
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite(leftMotorE, leftMotorSpeed);

    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotorE, rightMotorSpeed);
}

void turnCW(int leftMotorSpeed, int rightMotorSpeed)
{
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    analogWrite(leftMotorE, leftMotorSpeed);

    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite(rightMotorE, rightMotorSpeed);
}

void loop()
{
    moveStraight(100, 100);
    delay(20);
   /* turnCCW(100, 100);
    delay(2000);
    turnCW(100, 100);
    delay(2000);*/
}
