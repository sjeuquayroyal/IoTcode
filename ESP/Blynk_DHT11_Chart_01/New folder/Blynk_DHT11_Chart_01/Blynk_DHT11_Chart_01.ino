#include <Blynk.h>
#include<WiFi.h>
#include<DHT.h>
#include<BlynkSimpleEsp32.h>
#include<HttpClient.h>


char token[] = "ankJrDtVKIKC_kH0nUGD247URtVoeeDQ";
const char* ssid = "Lau 1 The 80's icafe";
const char* password = "the80sicafe";

//Khai bao cho DHT11
#define relay 13
#define led 25
#define light 35
#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendata(){
float t = dht.readTemperature();
float h = dht.readHumidity();
int LDR = analogRead(light);
Serial.print("Tem: ");
Serial.println(t);
Serial.print("Hum: ");
Serial.println(h);
Serial.print("Light: ");
Serial.println(LDR);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V6, LDR-1200);
    if(LDR <900)
  {
   digitalWrite(led, LOW);
  }
  else
  {
 digitalWrite(led, HIGH);
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


BLYNK_WRITE(V0){
   int value=param.asInt();
  if(value==1){
     digitalWrite(relay, HIGH);
  }else{
    digitalWrite(relay, LOW);
  }
}
