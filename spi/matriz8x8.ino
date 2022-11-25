#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>    //  max7219 library


// Uncomment according to your hardware type
//#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
int pinCS = 5;

Max72xxPanel matrix = Max72xxPanel(pinCS, 1, 1);

void handleNewMessages(String tx) {


    String text = tx;

    //Draw scrolling text
    int spacer = 1;                            // This will scroll the string
    int width = 5 + spacer;                    // The font width is 5 pixels
    for ( int i = 0 ; i < width * text.length() + width + 2; i++ ) {
      matrix.fillScreen(0);

      int letter = i / width;
      int x = (matrix.width() - 1) - i % width;
      int y = (matrix.height() - 8) / 2; // center the text vertically

      while ( x + width - spacer >= 0 && letter >= 0 ) {
        if ( letter < text.length() ) {
          matrix.drawChar(x, y, text[letter], 1, 0, 1);
        }
        letter--;
        x -= width;
      }
      matrix.write(); // Send bitmap to display

      delay(100);
    }
  
}

void setup() {

  matrix.setIntensity(4); // Set brightness between 0 and 15

}

void up(int intensidad){
  matrix.drawPixel(4,1,intensidad);
  matrix.drawLine(3,2,5,2,intensidad);         
  matrix.drawLine(2,3,6,3,intensidad);         
  matrix.drawLine(1,4,7,4,intensidad);         
  matrix.drawLine(3,5,5,5,intensidad);         
  matrix.drawLine(3,6,5,6,intensidad);         
  matrix.drawLine(3,7,5,7,intensidad);         
  matrix.write();            // Draws the buffer to the display.
}
void down(int intensidad){
  matrix.drawPixel(4,7,intensidad);
  matrix.drawLine(3,6,5,6,intensidad);         
  matrix.drawLine(2,5,6,5,intensidad);         
  matrix.drawLine(1,4,7,4,intensidad);         
  matrix.drawLine(3,1,5,1,intensidad);         
  matrix.drawLine(3,2,5,2,intensidad);         
  matrix.drawLine(3,3,5,3,intensidad);         
  matrix.write();            // Draws the buffer to the display.
}
void loop() {
  matrix.fillScreen(0);      //This will fill the display. The parameter controls the colour.
  down(0);  
  up(1);
  delay(1000);
   up(0);
  down(1);
  delay(1000);
  handleNewMessages("Embebidos ");

}
