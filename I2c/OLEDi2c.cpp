#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void displayMessage(const char* message) {
  display.clearDisplay();
  
  // Ajustar tamaño y posición del texto
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  
  // Mostrar el mensaje en la pantalla
  display.println(message);
  display.display();
}


void setup() {
  Serial.begin(115200);
  // Inicializar la comunicación I2C
  Wire.begin();

  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error al inicializar el display SSD1306");
    while (true);
  }

  // Borrar la pantalla
  display.clearDisplay();
  display.setTextSize(3);
  // Mostrar mensaje manual

  display.fillCircle(64,32,20,WHITE);
  
  displayMessage("Hola, Taller IV!");
  delay(3000);
  displayMessage("Hola, mundo!");
}

void loop() {
  // El código del bucle principal va aquí
}
