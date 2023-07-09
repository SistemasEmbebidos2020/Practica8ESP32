#include <Arduino.h>
#include <BluetoothSerial.h>
bool emparejado = false;
BluetoothSerial SerialBT;

void conect_succes(){
  while (!emparejado)
  {
    if (!SerialBT.connected())
    {
      Serial.println("Esperando emparejamiento...");
      delay(1000);
    }
    else
    {
      Serial.println("Emparejado con el esclavo");
      emparejado = true;
    }
  }
}

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32_Esclavo");  // Nombre del dispositivo Bluetooth del esclavo
  SerialBT.connect("ESP32_Master"); // Nombre del dispositivo Bluetooth del maestro
  Serial.println("ESP32 esclavo iniciado");
}

void loop()
{
  conect_succes();   //No saldrá de esta función hasta que se conecte correctamente con el dispositivo colocado en SerialBT.connect

  if (SerialBT.available())
  {
    Serial.print(SerialBT.readString());
  }

  if (Serial.available())
  {
    SerialBT.print(Serial.readString());
  }
}
