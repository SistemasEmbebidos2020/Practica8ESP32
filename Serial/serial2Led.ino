#include <Arduino.h>

#define LED 2

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(LED,OUTPUT);
  
      digitalWrite(LED,HIGH);
      delay(1500);
      digitalWrite(LED,LOW);
}

void loop() {

  if (Serial2.available() > 0){
    String v = Serial2.readStringUntil('\n');
    Serial.println(v);
    if (v.startsWith("on")){	//verificamos si lo recibido empieza con on
      digitalWrite(LED,HIGH);
    }else if (v.startsWith("off"))	//verificamos si lo recibido empieza con off 
     digitalWrite(LED,LOW);
  }
}
