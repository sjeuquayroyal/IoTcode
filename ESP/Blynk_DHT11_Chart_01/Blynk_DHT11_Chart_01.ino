#include <Blynk.h>
#include<WiFi.h>
#include<DHT.h>
#include<BlynkSimpleEsp32.h>
#include<HttpClient.h>
#define relay 33
#define led 34
#define light 35
char token[] = "ankJrDtVKIKC_kH0nUGD247URtVoeeDQ";
const char* ssid = "Lau 1 The 80's icafe";
const char* password = "the80sicafe";
//Khai bao cho DHT11
#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendata(){
float t = dht.readTemperature();
float h = dht.readHumidity();
int LDR = analogRead(light);
Serial.println("Tem");
Serial.println(t);
Serial.println("Hum");
Serial.println(h);
Serial.println("Light");
Serial.println(LDR);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V5, LDR);
  Blynk.virtualWrite(V6, LDR);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
    if(LDR <50)
  {
//    digitalWrite(led, LOW);
  }
  else
  {
//    digitalWrite(led, HIGH);
//    delay(1000);
  }
}
void setup() {
  // put your setup code here, to run once:
    pinMode(led, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Dang ket noi...");
    delay(500);
  }
  Serial.println("Da ket noi thanh cong!!!");

  Blynk.begin(token, ssid, password);
  dht.begin();
  pinMode(light, INPUT);
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  timer.setInterval(3000L, sendata);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
BLYNK_WRITE(V3){
  int value = param.asInt();
  if(value==0){
    digitalWrite(relay, LOW);
  }else{
    digitalWrite(relay, HIGH);
  }
}
