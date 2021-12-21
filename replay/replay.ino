#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char token[] = " llr2HhLOT1rgKfJMjC0X6ALk0UMVG3TR";
const char* ssid = "ZTE-c29af6";
const char* password = "38d82fc2";

BlynkTimer timer;

void sendata(){
  digitalWrite(32, HIGH);
  Blynk.virtualWrite(V0, 1);
  delay(5000);
  Blynk.virtualWrite(V0, 0);
  digitalWrite(32, LOW);
  delay(5000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Dang ket noi...");
    delay(500);
  }
  Serial.println("Da ket noi thanh cong!!!");
  Blynk.begin(token, ssid, password);
  pinMode(32,OUTPUT);
  timer.setInterval(5000L, sendata);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();  
  timer.run();
}
