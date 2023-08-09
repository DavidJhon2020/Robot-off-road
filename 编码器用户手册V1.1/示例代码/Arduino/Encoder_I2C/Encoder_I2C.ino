#include <PinChangeInterrupt.h>
#include <MotorDriver.h>

#define ENCODEROUTPUT 12  // 每次旋转插入电机编码器输出脉冲
#define ENCODER_A 2       //编码器检测引脚
int Val = 4096;           //电机占空比 0-4096;

int interval = 1000;       //采样时间
int rpm = 0;
long previousMillis = 0;
long currentMillis = 0;
volatile long encoderValue = 0;
bool testflag = false;
#define MOTORTYPE YF_IIC_TB   //
uint8_t SerialDebug = 1; // 串口打印调试 0-否 1-是

const int offsetm1 = -1;
const int offsetm2 = 1;
const int offsetm3 = -1;
const int offsetm4 = 1;

MotorDriver motorDriver = MotorDriver(MOTORTYPE);

void setup()
{
  Serial.begin(115200); // 波特率
  motorDriver.begin();
  motorDriver.motorConfig(offsetm1, offsetm2, offsetm3, offsetm4);
  delay(1000);   // wait 2s
  pinMode(ENCODER_A, INPUT_PULLUP); // 将霍尔传感器A设置为输入上拉
  // 在每个上升信号上在霍尔传感器A处附加中断
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), updateEncoder, RISING);
  //引脚改变中断
//  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENCODER_A), updateEncoder, RISING);
}

void loop()
{
  motorDriver.setSingleMotor(M1, Val);   // 电机M1 1500/4096 正转
    currentMillis = millis();   //每秒更新RPM值
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    // 每分钟转数（RPM）= （编码器总脉冲数/电机编码器输出）x 60s
    rpm = (float)(encoderValue * 60 / ENCODEROUTPUT);
    //换算小车速度M/S，65mm直径轮子，减速比4.5：1
    float Speed = (rpm * 0.2 / 4.5 / 60);
    Serial.print(encoderValue);
    Serial.print(" cpr ");
    Serial.print(rpm);
    Serial.print(" RPM  ");  //电机转速
    Serial.print(Speed);
    Serial.println(" m/s");  //小车速度
    encoderValue = 0;
  }
}

void updateEncoder()
{
  encoderValue++;
}
