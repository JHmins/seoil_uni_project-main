#include "board.h"
#include "Arduino.h"
#include <adafruit_NeoPixel.h>
#define SERIAL_NUM 2
#define RED   0x200000
#define GREEN 0x002000
#define BLUE  0x000020
#define WHITE  0x101010
#define BLACK  0x000000
#define CUSTOM 0x0f2f1f

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(SERIAL_NUM,RGB_LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t color_table[] {
  RED,
  GREEN,
  BLUE,
  WHITE,
  BLACK,
  CUSTOM,
};
#define COLOR_TABLE_SIZE  (sizeof(color_table)/sizeof(color_table[0]))
void setup() {
    pixels.begin();
}
void loop() {
  for(int color=0; color < COLOR_TABLE_SIZE; color++ ){
      pixels.setPixelColor(0, pixels.Color(color_table[color]>>16 , (uint8_t)(color_table[color]>>8) , (uint8_t)color_table[color] )); 
      pixels.setPixelColor(1, pixels.Color(color_table[COLOR_TABLE_SIZE-1-color]>>16 , (uint8_t)(color_table[COLOR_TABLE_SIZE-1-color]>>8)\
      , (uint8_t)color_table[COLOR_TABLE_SIZE-1-color] )); 
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(1000);
  }
}
