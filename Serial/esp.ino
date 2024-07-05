// Arduino

#include <Arduino.h>

int LED1 = 2;
int LED2 = 4;

void setup()
{
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

String lectura;
void loop()
{
  delay(10);
  if (Serial.available() > 0)
  {
    lectura = Serial.readString();
    Serial.println(lectura);
  }
  if (lectura == "1")
  {
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 1);
  }

  else if (lectura == "2"){
     digitalWrite(LED1, 1);
    digitalWrite(LED2, 0);
  }
  else if (lectura == "3"){
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
  }
  else if (lectura == "4"){
      digitalWrite(LED1, 0);
    digitalWrite(LED2, 1);
  }
}
