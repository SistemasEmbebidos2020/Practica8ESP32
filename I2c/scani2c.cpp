#include <Wire.h>

void setup() {
    Wire.begin(); // Iniciar comunicación I2C
    Serial.begin(115200);
}

void loop() {
    byte error, address;
    int devices = 0;

    Serial.println("Escaneando direcciones I2C...");

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("Dispositivo encontrado en dirección 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            devices++;
        }
    }

    if (devices == 0) {
        Serial.println("No se encontraron dispositivos I2C.");
    } else {
        Serial.print("Total de dispositivos encontrados: ");
        Serial.println(devices);
    }

    delay(5000); // Esperar 5 segundos antes de volver a escanear
}
