
void setup() {
  // put your setup code here, to run once:
pinMode(1,OUTPUT);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
}

void loop() {
digitalWrite(1,HIGH);
digitalWrite(6,HIGH);
delay(7000);
digitalWrite(6,LOW);
digitalWrite(5,HIGH);
delay(1000);
digitalWrite(5,LOW);
digitalWrite(1,LOW);
digitalWrite(4,HIGH);
digitalWrite(3,HIGH);
delay(7000);
digitalWrite(3,LOW);
digitalWrite(2,HIGH);
delay(1000);
digitalWrite(2,LOW);
digitalWrite(4,LOW);
}
