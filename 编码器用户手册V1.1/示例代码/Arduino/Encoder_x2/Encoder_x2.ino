/************************************
  主控驱动板为：Arduino UNO
  电机驱动：L298N
*************************************/
#define ENCODEROUTPUT 12  // 每次旋转插入电机编码器输出脉冲(cpr)

#define encoderA   2      // 中断检测端口，数字口D2
#define encoderB   3      // 普通端口，数字口D3

#define IN1  4            // DIR pin 4
#define IN2  5            // DIR pin 5
#define EN1  6            // PWM pin 6

int Val = 255;            //电机占空比 0-255;
int rpm = 0;
int interval = 1000;      //采样时间1s
long previousMillis = 0;
long currentMillis = 0;
volatile long encoderValue = 0;

void setup() {
  Serial.begin(9600);     // 波特率
  pinMode(encoderA, INPUT_PULLUP); // 将霍尔传感器A设置为输入上拉
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // 在每个信号变化时在霍尔传感器A处附加中断
  attachInterrupt(digitalPinToInterrupt(encoderA), EncoderA, CHANGE);
}

void loop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, Val);

  currentMillis = millis();    //每秒更新RPM值
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    Serial.print("PWM:");
    Serial.print(Val);
    Serial.print('\t');
    Serial.print("  ENCODER:");
    Serial.print(encoderValue);
    Serial.println(" pulse");
    encoderValue = 0;
  }
}

void EncoderA() {
  if (digitalRead(encoderA) == HIGH) {
    if (digitalRead(encoderB) == LOW) {
      encoderValue++;
    } else {
      encoderValue--;
    }
  } else {
    if (digitalRead(encoderB) == LOW) {
      encoderValue--;
    } else {
      encoderValue++;
    }
  }
}
