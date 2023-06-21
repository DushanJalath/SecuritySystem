//vcc -5v, grnd-grnd,cli-6,reset-8,dat-7

#include <virtuabotixRTC.h>
#include "esp32.h"
#include "fingerprint.h"
#include "gsm.h"
#include "pins.h"
#include "pir.h"
#include "requests.h"
#include "switch.h"
#include "led.h"
//rtc

virtuabotixRTC myRTC(CLK_PIN, DAT_PIN, RST_PIN);




void setup()  {
  Serial.begin(115200);
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(0, 21, 16, 3, 21,6,2023);
  pinMode(PIR, INPUT);  // Set the PIR pin as input
  pinMode(LOCK_PIN,OUTPUT);
  pinMode(S_LED,OUTPUT);
  pinMode(F_LED,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(RST_SWH,INPUT_PULLUP);
}

void loop()  {
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();
  loop_switch();

  if(myRTC.hours == 8 && myRTC.minutes >=0 & myRTC.minutes<=31){ 
    if(wifi_loop()=="1" && fingerprint_loop()==1){
      sucLED();
      digitalWrite(LOCK_PIN,HIGH);
      delay(20000);
      digitalWrite(LOCK_PIN,LOW);
    }
  }else{
    pirDetection();
    message();
  }

  // Delay so the program doesn't print non-stop
  delay(1000);

 
}