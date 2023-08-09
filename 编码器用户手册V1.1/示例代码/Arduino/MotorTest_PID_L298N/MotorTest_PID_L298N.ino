/*************************************************************************************
   Motor pid test with L298N
   
   RS365 ENCODER MOTOR, 24cpr, 
   Motherboard : Arduino UNO
   Motor drive: L298N
   Power supply 3s:18650 or Li-Po
   by:YFROBOT
 *************************************************************************************/
#include <PID_v1.h>
#include <PinChangeInterrupt.h>

#define Encoder1A  2      //A pin -> the interrupt pin 2
#define Encoder2A  3      //A pin -> the interrupt pin 3

//L298N Motor Driver variables
#define DIR1A  4     //M1 Direction Control
#define DIR1B  5
#define PWM1   6

volatile double encoderPos1 = 0;
//PID variables
//double Kp1 = 1.07, Ki1 = 3.15, Kd1 = 0.0426;  //Adjust the PID to fit the motor
double Kp1 = 0.6, Ki1 = 5, Kd1 = 0.02;  //Adjust the PID to fit the motor
double Setpoint1, Input1, Output1;
PID myPID1(&Input1, &Output1, &Setpoint1, Kp1, Ki1, Kd1, DIRECT);
float last = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(DIR1A, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(Encoder1A, INPUT_PULLUP);                  // quadrature encoder1 input A
  pinMode(Encoder2A, INPUT_PULLUP);                  // quadrature encoder2 input A
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(Encoder1A), Encoder1, FALLING);
  myPID1.SetMode(AUTOMATIC);
  myPID1.SetOutputLimits(0, 255);
  delay(100);
}

void loop() {
  if ( millis() - last > 100)
  {
    double rpm1 = count_rpm1();
    Input1 = map(rpm1, 0, 30 , 0, 255);
  }

  Setpoint1 = 100;
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR1B, LOW);
  myPID1.Compute();
  analogWrite(PWM1, Output1);

  Serial.print("Setpoint1:");
  Serial.print(Setpoint1);
  Serial.print("   Input1:");
  Serial.print(Input1);
  Serial.print("   Output1:");
  Serial.println(Output1);
}

void Encoder1() {
  ++encoderPos1;
}

double count_rpm1() {
  double rpm1 = encoderPos1 / 24 * 1000 / (millis() - last);
  encoderPos1 = 0;
  last = millis();
  return rpm1;
}
