//https://github.com/nhatuan84/esp32-micro-sdcard/blob/master/examples/nanosdcard2/nanosdcard2.ino

#include <SPI.h>
#include <mySD.h>
#include "board.h"

File myFile;

void setup() {
  Serial.begin(115200);
  
   Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on Arduino Uno boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(SD_CS_PIN, OUTPUT);

  if (!SD.begin(SD_CS_PIN, SPI2_MOSI_PIN, SPI2_MISO_PIN, SPI2_SCK_PIN)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
	// close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop(){
}