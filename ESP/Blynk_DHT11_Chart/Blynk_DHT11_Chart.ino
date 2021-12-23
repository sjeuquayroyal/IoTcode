#include <Blynk.h>
#include<WiFi.h>
#include<DHT.h>
#include<BlynkSimpleEsp32.h>
#include<HttpClient.h>

#define led 33
#define sensor A0
char token[] = "ankJrDtVKIKC_kH0nUGD247URtVoeeDQ";
const char* ssid = "ZTE-c29af6";
const char* password = "38d82fc2";
const int ledPin = 26;
const int ldrPin = A0;
int relay =19;
//Khai bao cho DHT11
#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendata(){
float t = dht.readTemperature();
float h = dht.readHumidity();
int LDR = analogRead(sensor);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
   Blynk.virtualWrite(V5, LDR);
  
    if(LDR <50)
  {
    digitalWrite(led, HIGH);
    Blynk.virtualWrite(V5, "Light ON");
  }
  else
  {
    digitalWrite(led, LOW);
    Blynk.virtualWrite(V5, "Light OFF");
   
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
  pinMode(ledPin, OUTPUT);

pinMode(ldrPin, INPUT);
  timer.setInterval(3000L, sendata);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
BLYNK_WRITE(V3){
  int value = param.asInt();
  digitalWrite(relay_fan, value);
}
