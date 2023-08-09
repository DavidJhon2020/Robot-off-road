#include<SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int  adc_key_val[5] = {30, 150, 360, 535, 760 };
word lcd_key_input;
byte keyVal = 0;
unsigned int key = -1;
int NUM_KEYS = 5;
int pulses;                              //Output pulses.
int deg = 0;
int encoderA = 3;
int encoderB = 2;
const int pwm = 6;                      //Power of motor.
const int dir1 = 4;                       //Direction of the motor.
const int dir2 = 5;                       //Direction of the motor.
int pulsesChanged = 0;
#define total 245                        //x1 pulses per rotation.
#define motorSpeed 180                   //Change speed of the motor.
void setup(){
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("x1 ENCODER");lcd.print("     ");
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  pinMode(pwm, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);  
  analogWrite(pwm,0);
  digitalWrite(dir1,HIGH);
  digitalWrite(dir2,LOW);
  waitAnyKeyPress();
  attachInterrupt(0, A_CHANGE, CHANGE);


}//setup

void loop(){
 if (pulses == total) {
    analogWrite(pwm, 0);
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, LOW);
  }
  else {
    if (pulses > total) {
      analogWrite(pwm, motorSpeed);
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, HIGH);

    }
    else if (pulses < total) {
      analogWrite(pwm, motorSpeed);
      digitalWrite(dir1, HIGH);
      digitalWrite(dir2, LOW);
    }
  }
  
  if (pulsesChanged != 0) {
    pulsesChanged = 0;
    lcd.setCursor(0,1);
    lcd.print("Pulses:");lcd.print(pulses);lcd.print("          ");
    Serial.println(pulses);
  }
}

void A_CHANGE(){                                  //Function that to read the pulses in x1.
  if( digitalRead(encoderB) == 0 ) {
    if ( digitalRead(encoderA) == 0 ) {
      // A fell, B is low
      pulses--; // moving reverse
    } else {
      // A rose, B is low
      pulses++; // moving forward
    }
  }
  pulsesChanged = 1;
}

void waitAnyKeyPress(void)                          //Function that delay until any button of LCD pressed.
{
  while (1)
  {
    lcd_key_input = analogRead(0);
    int key = get_key(lcd_key_input);
    if (key != -1)
      break;
  }
}

int get_key(unsigned int input)                     //Function to recognize the LCD button.
{
  int k;

  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {

      return k;
    }
  }

  if (k >= NUM_KEYS)
    k = -1;     // No valid key pressed

  return k;
}

