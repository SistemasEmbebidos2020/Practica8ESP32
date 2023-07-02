#include <Arduino.h>
#include <BluetoothSerial.h>
long ti = millis();
BluetoothSerial SerialBT;
bool emparejado = false;
void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32_Master", true); // Nombre del dispositivo Bluetooth del maestro el valor de true para activar master
  SerialBT.connect("ESP32_Esclavo");    // Nombre del dispositivo Bluetooth del esclavo
  Serial.println("ESP32 maestro iniciado");
}

void loop()
{
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

  if (SerialBT.available())
  {
    Serial.print(SerialBT.readString());
  }

  if (Serial.available())
  {
    SerialBT.print(Serial.readString());
  }
}
