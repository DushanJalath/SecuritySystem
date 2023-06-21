#include "pins.h"

void lockFunc(){
  digitalWrite(LOCK_PIN,HIGH);
  //delay(1000);
  for(int i = 0; i<20; i++){
    
    digitalWrite(BUZZER_PIN,HIGH);
    delay(250);
    digitalWrite(BUZZER_PIN,LOW);
    delay(250);
    }
  digitalWrite(LOCK_PIN,LOW);
  delay(1000);

}
// void setup_switch(){
//   pinMode(BUZZER_PIN,OUTPUT);
//   pinMode(LOCK_PIN,OUTPUT);
//   pinMode(RST_SWH,INPUT_PULLUP);

// }

void loop_switch(){
  int state = false;
 if(digitalRead(RST_SWH) == LOW){
   state = true;
 }
 if(state){
   lockFunc();
   state = false;
 }

}