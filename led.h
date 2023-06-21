#include "pins.h"
void sucLED();
void fLED();

void sucLED(){
  digitalWrite(S_LED,HIGH);
  delay(1000);
  digitalWrite(S_LED,LOW);
  delay(1000);
}

void fLED(){
  digitaWrite(F_LED,HIGH);
  delay(20000);
  digitaWrite(F_LED,LOW);
  delay(20000);
}