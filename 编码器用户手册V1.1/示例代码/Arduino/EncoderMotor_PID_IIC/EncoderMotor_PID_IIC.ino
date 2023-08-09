/*************************************************************************************
   Motor pid test with pot

   RS365 ENCODER MOTOR, 24cpr,
   Motherboard : Arduino UNO
   Motor drive: L298N
   Power supply 3s:18650 or Li-Po
   by:YFROBOT
 *************************************************************************************/
#include <PID_v1.h>
#include <PinChangeInterrupt.h>
#include <MotorDriver.h>
int pot = A0;
#define Encoder1A  2     // 电机1A相 D4 交换黄白线的接线端口
#define Encoder1B  4     // 电机1B相 D2 

volatile double encoderPos1 = 0;
//volatile double encoderPos2 = 0;
//PID variables
//double Kp1 = 1.07, Ki1 = 3.15, Kd1 = 0.0426;  //Adjust the PID to fit the motor
double Kp1 = 15, Ki1 = 5, Kd1 = 0.02;  //Adjust the PID to fit the motor
double Setpoint1, Input1, Output1;
PID myPID1(&Input1, &Output1, &Setpoint1, Kp1, Ki1, Kd1, DIRECT);
float last = 0;

#define MOTORTYPE YF_IIC_TB   //
uint8_t SerialDebug = 0; // 串口打印调试 0-否 1-是

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetm1 = 1;
const int offsetm2 = 1;
const int offsetm3 = 1;
const int offsetm4 = -1;

// Initializing motors.
MotorDriver motorDriver = MotorDriver(MOTORTYPE);

void setup()
{
  Serial.begin(115200);
  TCCR1B = TCCR1B & 0b11111000 | 1;                   // set 31KHz PWM to prevent motor noise
  pinMode(Encoder1A, INPUT_PULLUP);                  // quadrature encoder1 input A
  pinMode(Encoder1B, INPUT_PULLUP);                  // quadrature encoder1 input B
  //  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(Encoder1A), Encoder1, FALLING);
  //  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(Encoder1B), Encoder2, FALLING);
  attachInterrupt(digitalPinToInterrupt(Encoder1A), Encoder1, CHANGE);
  //  attachInterrupt(digitalPinToInterrupt(Encoder1B), Encoder2, FALLING);
  myPID1.SetMode(AUTOMATIC);
  myPID1.SetSampleTime(1);
  myPID1.SetOutputLimits(-4096, 4096);
  motorDriver.begin();
  motorDriver.motorConfig(offsetm1, offsetm2, offsetm3, offsetm4);
  delay(300);
}

void loop() {
  //  Setpoint1 = analogRead(pot) / 1.59375;
  //  Setpoint1 = analogRead(pot)*1.595307917888;
  //  int Set = map(Setpoint1, 0, 1632, 0, 360);
  //  Input1 = encoderPos1 ;
  //  int Output = map(Input1, 0, 1632, 0, 360);
  Setpoint1 = analogRead(pot) * 6.65;
  int Set = map(Setpoint1, 0, 6802, 0, 360);
  Input1 = encoderPos1 ;
  int Output = map(Input1, 0, 6802, 0, 360);
  myPID1.Compute();
    Serial.print(" Setpoint1: ");
    Serial.print(Setpoint1);
  Serial.print("    Set: ");
  Serial.print(Set);
  Serial.print("°");
      Serial.print("           Input1: ");
    Serial.print(Input1);
  Serial.print("  Output: ");
  Serial.print(Output);
  Serial.println("°");
  //  Serial.print("   Output1:");
  //  Serial.println(Output1);
  moveMotor(Output1, 0, 0, 0); // 电机M1,M2,M3,M4 运动
}

void moveMotor(int16_t speed1, int16_t speed2, int16_t speed3, int16_t speed4) {
  if (speed1 > 0)
    speed1 = min(speed1, 4096);
  else
    speed1 = max(speed1, -4096);
  if (speed2 > 0)
    speed2 = min(speed2, 4096);
  else
    speed2 = max(speed2, -4096);
  if (speed3 > 0)
    speed3 = min(speed3, 4096);
  else
    speed3 = max(speed3, -4096);
  if (speed4 > 0)
    speed4 = min(speed4, 4096);
  else
    speed4 = max(speed4, -4096);
  motorDriver.setMotor(speed1, speed2, speed3, speed4);
}

void Encoder1() {
  if (digitalRead(Encoder1A) == HIGH) {
    if (digitalRead(Encoder1B) == LOW) {
      encoderPos1++;
    } else {
      encoderPos1--;
    }
  } else {
    if (digitalRead(Encoder1B) == LOW) {
      encoderPos1--;
    } else {
      encoderPos1++;
    }
  }
}

//void Encoder2() {
//  if (digitalRead(Encoder1B) == HIGH) {
//    if (digitalRead(Encoder1A) == LOW) {
//      encoderPos1--;
//    } else {
//      encoderPos1++;
//    }
//  } else {
//    if (digitalRead(Encoder1A) == LOW) {
//      encoderPos1++;
//    } else {
//      encoderPos1--;
//    }
//  }
//}


//rpm = 1秒的转速，除以减速比得到电机输出轴的转速，再结合轮子的大小计算出小车的速度 mm/s 或 m/s 等。
