// IR Sensors
int sensor1 = A0;      // Left most sensor
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;      
int sensor5 = A4;
int sensor6 = A5;
int sensor7 = 2;
int sensor8 = 3;       // Right most sensor

// Initial Values of Sensors
int sensor[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// Motor Variables
int ENA = 6;
int motorInput1 = 11;
int motorInput2 = 10;
int motorInput3 = 13;
int motorInput4 = 12  ;
int ENB = 5;

//Initial Speed of Motor
int initial_motor_speed = 140;

// Output Pins for Led
int ledPin1 = 7;
//int ledPin2 = A4;

// PID Constants
float Kp = 25;
float Ki = 0;
float Kd = 15;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

void setup()
{
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
  pinMode(sensor7, INPUT);
  pinMode(sensor8, INPUT);

  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(ledPin1, OUTPUT);
//  pinMode(ledPin2, OUTPUT);
//
 digitalWrite(ledPin1, LOW);
//  digitalWrite(ledPin2, LOW);

  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
//  delay(500);
//  Serial.println("Started !!");
//  delay(1000);
}
void loop()
{
    read_sensor_values();
    calculate_pid();
    motor_control();
    
    
}

void know_direction(){
    
}

void read_sensor_values()
{
  sensor[0] = !digitalRead(sensor1);
  sensor[1] = !digitalRead(sensor2);
  sensor[2] = !digitalRead(sensor3);
  sensor[3] = !digitalRead(sensor4);
  sensor[4] = !digitalRead(sensor5);
  sensor[5] = !digitalRead(sensor6);
  sensor[6] = !digitalRead(sensor7);
  sensor[7] = !digitalRead(sensor8);

  
    // Serial.print(sensor[0]);
    // Serial.print("\t");
    // Serial.print(sensor[1]);
    // Serial.print("\t");
    // Serial.print(sensor[2]);
    // Serial.print("\t");
    // Serial.print(sensor[3]);
    // Serial.print("\t");
    // Serial.print(sensor[4]);
    // Serial.print("\t");
    // Serial.print(sensor[5]);
    // Serial.print("\t");
    // Serial.print(sensor[6]);
    // Serial.print("\t");
    // Serial.println(sensor[7]);

    int mid_path_value = 450;

    int weighted_error = (700*sensor[0] + 600*sensor[1] + 500*sensor[2] + 400*sensor[3]
                            + 300*sensor[4] + 200*sensor[5] + 100*sensor[6] + 0*sensor[7]);

    int sum_of_sensors = sensor[0]+sensor[1]+sensor[2]+sensor[3]+sensor[4]+sensor[5]+sensor[6]+sensor[7];
    int avg_weighted_error = weighted_error/sum_of_sensors;
    error = ((avg_weighted_error*2) - (mid_path_value*2))/100;



}

void turn_direction(){
    int direction = sensor[0] - sensor[7];
    if (direction == 1){
        sharpLeftTurn();
    }
    else{
        sharpRightTurn();
    }

}

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed = initial_motor_speed + PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  /*Serial.print(PID_value);
    Serial.print("\t");
    Serial.print(left_motor_speed);
    Serial.print("\t");
    Serial.println(right_motor_speed);*/

  analogWrite(ENA, left_motor_speed); //Left Motor Speed
  analogWrite(ENB, right_motor_speed); //Right Motor Speed

  //following lines of code are to make the bot move forward
  forward();
}

void forward()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
void reverse()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void right()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}
void left()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void sharpRightTurn() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
void sharpLeftTurn() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void stop_bot()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}
