#include <HttpClient.h>




#include<WiFi.h>
#include<DHT.h>

#include<string.h>
const char* ssid = "ZTE-c29af6";
const char* password = "An2111an";

//Khai bao cho DHT11
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Khai bao api url
String apiURL = "https://api.thingspeak.com/update?api_key=PYNZNJW9R3XXM38Y";

void senddata(const char* url);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Dang ket noi...");
    delay(500);
  }
  Serial.println("Da ket noi thanh cong!!!");
  dht.begin();
}

void loop() {
  //Doc gia tri cam bien
  int t = rand() % 50;
  int h = rand() % 100;

  //Kiem tra gia tri cam bien
  if(isnan(t) || isnan(h)){
    Serial.println("Doc gia tri cam bien bi loi!!!");
    return;
  }
  
  Serial.print("Nhiet do: ");
  Serial.println(t);
  Serial.print("Am do: ");
  Serial.println(h);
  Serial.println("------------------------------------");
  
  char param[100];
  sprintf(param, "&field1=%d&field2=%d",t,h);

  String url = apiURL + String(param);
  senddata(url.c_str());
  delay(60000);
}

void senddata(const char* url){
  HTTPClient http;
  //Tao ket noi esp voi thingspeak
  http.begin(url);
  //Gui di va nhan ket qua phan hoi
  int responsecode = http.GET();
  String responsebody = "{}";
  if(responsecode > 0){
    Serial.print("Response code: ");
    Serial.println(responsecode);
    responsebody = http.getString();
  }
  else{
    Serial.print("Error code: ");
    Serial.println(responsecode);
  }
  http.end();
  Serial.println(responsebody);
}
