k
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int buzzer = 10;
int sensor_DAD = A0;

int light_yellow = 8;


int value_flame;

int value_DAD;


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(buzzer, OUTPUT);
  pinMode(light_yellow, OUTPUT);
  
  pinMode(sensor_DAD, INPUT); 
  
  digitalWrite(light_yellow, LOW);
  digitalWrite(buzzer, HIGH);
  
}

void loop() {
  value_DAD = analogRead(sensor_DAD);
  
  int value_DAD_virtual = map(value_DAD, 0, 1023, 0, 100);
  int value_DAD_real = 100 - value_DAD_virtual;
  
  if (value_DAD_real => 50){
    lcd.setCursor(0,0);
    lcd.print("Home -> Water");
    delay(100);
    digitalWrite(light_yellow,HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    digitalWrite(light_yellow, LOW);
    delay(100);
  }
  lcd.setCursor(0,0);
  lcd.print("Value: ");
  lcd.print(value_DAD_real);
  lcd.print("%");
  lcd.print("     ");
  digitalWrite(buzzer, HIGH); 
  delay(100);
}
