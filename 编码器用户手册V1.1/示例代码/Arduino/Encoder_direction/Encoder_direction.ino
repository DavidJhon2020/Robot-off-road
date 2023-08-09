/************************************
  主控驱动板为：Arduino UNO

*************************************/
#define ENCODEROUTPUT 12  // 每次旋转插入电机编码器输出脉冲(cpr)

#define encoderA   2      // 中断检测端口，数字口D2
#define encoderB   3      // 普通端口，数字口D3

int rpm = 0;
int interval = 1000;      //采样时间1s
long previousMillis = 0;
long currentMillis = 0;
volatile long encoderValue = 0;

void setup() {
  Serial.begin(9600);     // 波特率
  pinMode(encoderA, INPUT_PULLUP); // 将霍尔传感器A设置为输入上拉

  // 在每个信号变化时在霍尔传感器A处附加中断
  attachInterrupt(digitalPinToInterrupt(encoderA), EncoderA, CHANGE);
}

void loop() {

  currentMillis = millis();    //每秒更新值
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

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
