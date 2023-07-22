#include <Arduino.h>
#include <BluetoothSerial.h>
bool emparejado = false;  // Se establece la variable emparejado para saber si se a conectado a un bluetooth
BluetoothSerial SerialBT; // Se estable una variable SerialBT para poder hacer uso de los comandos
int led1 = 2;             // Se define la variable led1 con el valor de 2, pin GIOP2 a utilizarse como salida para el led

void connect_successful()
{
  while (!emparejado) //
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
  SerialBT.begin("ESP32_Esclavo1");         // Nombre del dispositivo Bluetooth del esclavo
  SerialBT.setPin("bebe");                  // Establecer clave para conexion segura bluetooth
  Serial.println("ESP32 esclavo iniciado"); // Se Imprime mensaje indicando que el bluetooth esclavo se inició
  pinMode(led1, OUTPUT);                    // Se establece pin led1=2 como salida
}

void loop()
{
  connect_successful(); // No saldrá de esta función hasta que se conecte correctamente con el dispositivo colocado en SerialBT.connect
  if (SerialBT.available())
  {                                   // Se espera a recibir algo por bluetooth
    String v = SerialBT.readString(); // Se guarda en la variable v, lo recibido por bluetooth
    Serial.println(v);                // Se imprimer en serial la variable v
    if (v == "on1")
    {
      digitalWrite(led1, HIGH); // se verifica si lo recibido por bluetooth es = a on1 --- para encender led1
    }
    else if (v == "off1")
    {
      digitalWrite(led1, LOW); // se verifica si lo recibido por bluetooth es = a off1 --- para apagar led1
    }
  }
}
