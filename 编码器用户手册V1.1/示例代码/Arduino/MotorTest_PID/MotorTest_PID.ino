/*************************************************************************************
   Motor pid test
   
   RS365 ENCODER MOTOR, 24cpr, 
   Motherboard : Arduino UNO
   Motor drive: L298N
   Power supply 3s:18650 or Li-Po
   by:YFROBOT
 *************************************************************************************/
#include <PID_v1.h>
#include <PinChangeInterrupt.h>

#define EncoderA  2      //A pin -> the interrupt pin 2
#define EncoderB  3      //A pin -> the interrupt pin 3

//L298N Motor Driver variables
#define IN1  4     //M1 Direction Control
#define IN2  5
#define EN1  6

volatile double encoderPos = 0;
//PID variables
//double Kp1 = 1.07, Ki1 = 3.15, Kd1 = 0.0426;  //Adjust the PID to fit the motor
double Kp = 0.65, Ki = 5.5, Kd = 0.05;  //Adjust the PID to fit the motor
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

float last = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);

  pinMode(EncoderA, INPUT_PULLUP);                  // quadrature encoder1 input A
  pinMode(EncoderB, INPUT_PULLUP);                  // quadrature encoder2 input A
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(EncoderA), Encoder, FALLING);
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255);
  delay(100);
}

void loop() {
  if ( millis() - last > 100)
  {
    double rpm = count_rpm();
    Input = map(rpm, 0, 105 , 0, 255);
  }
  Setpoint = 150;
  //Setpoint = map(analogRead(pot),0,1023,0,255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  myPID.Compute();
  analogWrite(EN1, Output);

  Serial.print("Setpoint:");
  Serial.print(Setpoint);
  Serial.print("   Input:");
  Serial.print(Input);
  Serial.print("   Output:");
  Serial.println(Output);

}

void Encoder() {
  ++encoderPos;
}

double count_rpm() {
  double rpm = encoderPos / 24 * 1000 / (millis() - last);
  encoderPos = 0;
  last = millis();
  return rpm;
}
