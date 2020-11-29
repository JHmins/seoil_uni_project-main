#include <Arduino.h>

int val = 0;
void setup() {
  Serial.begin(115200);
    }

void loop() {
  val = hallRead();
  Serial.println(val);//to graph 
}
