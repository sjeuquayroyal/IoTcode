#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int qtr = A0;
int led =A1;
void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
pinMode(qtr,INPUT);
pinMode(led,OUTPUT);
}

void loop() {
  lcd.clear();
  // put your main code here, to run repeatedly:
int  value = map(analogRead(qtr), 0, 1023, 0, 255);  
  analogWrite(led, value);
  lcd.print("Sensor: ");
  lcd.setCursor(8,0);
  lcd.print(value);
  delay(200);
}
