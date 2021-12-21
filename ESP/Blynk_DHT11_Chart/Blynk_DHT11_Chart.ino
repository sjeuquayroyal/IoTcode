#include <Blynk.h>
#include<WiFi.h>
#include<DHT.h>
#include<BlynkSimpleEsp32.h>
#include<HttpClient.h>

char token[] = "ankJrDtVKIKC_kH0nUGD247URtVoeeDQ";
const char* ssid = "ZTE-c29af6";
const char* password = "38d82fc2";
//Khai bao cho DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendata(){
float t = dht.readTemperature();
float h = dht.readHumidity();
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
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
  dht.begin();
  timer.setInterval(3000L, sendata);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
