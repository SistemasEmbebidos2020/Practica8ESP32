#include <Arduino.h>

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int led = 2;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Embebidos"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(led,OUTPUT);
}

void loop() {
  if (Serial.available()) {
    SerialBT.print(Serial.readString());
  }
  if (SerialBT.available()) {
    String v = SerialBT.readString();
    Serial.println(v);
    if (v == "on1") digitalWrite(led,HIGH);
    else if (v == "off1")  digitalWrite(led,LOW);
  }
  delay(20);
}
