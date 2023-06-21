//vcc -5v, grnd-grnd,cli-6,reset-8,dat-7

#include <virtuabotixRTC.h>
#include "esp32.h"
#include "fingerprint.h"
#include "gsm.h"
#include "pins.h"
#include "pir.h"
#include "requests.h"

//rtc


// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(clockPin, dataPin, resetPin);

//gsmMessage
void message(){
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+94761776047\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(1000);
  mySerial.print("Last Minute Engineers | lastminuteengineers.com"); //text content
  delay(1000);
  mySerial.write(26);
}

//gsmCall
void call(){
  mySerial.println("AT");
  delay(1000);
  mySerial.println("ATD+94761776047;"); // Replace with your p
}

//pir function
void pirDetection(){
  int pirValue = digitalRead(pirPin);  // Read the PIR sensor value

  if (pirValue == HIGH) {
    // Motion detected
    digitalWrite(buzzerPin,HIGH);
  } else {
    digitalWrite(buzzerPin,LOW);
    
  }

  delay(1000);  // Delay for 1 second
}

void sucessLED(){

}

void functionLED(){

}

void setup()  {
  Serial.begin(9600);
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(0, 57, 12, 5, 26,5,2023);
  pinMode(pirDataPin, INPUT);  // Set the PIR pin as input
  pinMode(lockPin,OUTPUT)
}

void loop()  {
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();


  if(myRTC.hours == 8 && myRTC.minutes >=0 & myRTC.minutes<=31){
    //fingerPrint

    //ask face recognition 
    
  }else{
    pirDetection();
    if (mySerial.available()) {
      Serial.write(mySerial.read());
    }if (Serial.available()) {
      mySerial.write(Serial.read());
    }
  }

  // Delay so the program doesn't print non-stop
  delay(1000);

 
}