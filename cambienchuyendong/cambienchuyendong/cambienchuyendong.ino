#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


int ledPin = 13;        // chọn chân 13 báo hiệu LED
int inputPin = 2;       // chọn ngõ tín hiệu vào cho PIR
int pirState = LOW;     // Bắt đầu với không có báo động
int val = 0;
int pinSpeaker = 10;    //chọn chân cho chuông khi có đột nhập
int relay =7;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(pinSpeaker, OUTPUT);
  pinMode(relay,OUTPUT);
}

void loop() {
if(digitalRead(2)==HIGH)
{
  lcd.clear();
  lcd.print("Co bien !!!");
  digitalWrite(relay,HIGH);
  tone(10,2500);
  digitalWrite(13,HIGH);
  delay(400);
  digitalWrite(13,LOW);
  noTone(10);

  delay(300);
  
}
else
{
  lcd.clear();
  lcd.print("Binh thuong !!!");
  digitalWrite(relay,LOW);
  delay(300);
}
}
