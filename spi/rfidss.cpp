#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         2    // Pin de reinicio (RST) del lector RC522
#define SS_PIN          5   // Pin SS (Slave Select) del lector RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia del lector RC522

void setup() {
  Serial.begin(115200);    // Iniciar comunicación serial
  SPI.begin();           // Iniciar comunicación SPI
  mfrc522.PCD_Init();    // Iniciar el lector RC522
  mfrc522.PCD_DumpVersionToSerial();  // Mostrar versión del lector en el monitor serial
  Serial.println("¡Listo para leer tarjetas RFID!");
}

void loop() {
  // Verificar si se detecta una tarjeta RFID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Obtener UID de la tarjeta
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    
    Serial.print("Tarjeta detectada. UID: ");
    Serial.println(cardUID);
    
    mfrc522.PICC_HaltA();   // Detener comunicación con la tarjeta
  }
}
