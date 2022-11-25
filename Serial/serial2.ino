#include <Arduino.h>

void setup() {
  Serial.begin(115200);		//cable usb
  Serial2.begin(115200);	// pines GIOP16 RX2 Y GIOP17 TX2
}

void loop() {

  if (Serial2.available() > 0){	//Se verifica que se haya ingresado un texto por serial0 o cable usb
    Serial.println(Serial2.readStringUntil('\n'));	//se lee el texto ingresado y se lo envia por el serial2
  }
}
