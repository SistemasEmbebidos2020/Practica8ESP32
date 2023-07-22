#include <Arduino.h>
#include <BluetoothSerial.h>
/* Añadir en platformio.ini las siguientes lineas al final:
lib_deps = 
	adafruit/Adafruit GFX Library@^1.11.7
	adafruit/Adafruit SSD1306@^2.5.7
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  //tamaño horizontal en pixeles de pantalla
#define SCREEN_HEIGHT 64  //tamaño vertical en pixeles de pantalla

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


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

  // Inicializar la comunicación I2C
  Wire.begin();
  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Error al inicializar el display SSD1306");
    while (true){}
  }
  Serial.println("conectado bien");
  delay(4000);
  // Borrar la pantalla
  display.clearDisplay();

  //Mostrar en pantalla mensajes permanentes
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 5);
  display.print("Led1-> ");
  display.setCursor(2, 14);
  display.print("Led2-> ");
  display.setCursor(2, 23);
  display.print("Led3-> ");
  display.display();
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
      display.writeFillRect(45, 5, 17, 7, BLACK);
      display.setCursor(45, 5);
      display.print("ON");
      display.display();
    }
    else if (v == "off1")
    {
      digitalWrite(led1, LOW); // se verifica si lo recibido por bluetooth es = a off1 --- para apagar led1
      display.writeFillRect(45, 5, 17, 7, BLACK);
      display.setCursor(45, 5);
      display.print("OFF");
      display.display();
    }
  }
}
