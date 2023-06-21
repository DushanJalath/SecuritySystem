#include <HardwareSerial.h>
#include "pins.h"

HardwareSerial mySerial(0); // RX, TX

void call();
void message();

void gsm_setup();
void gsm_loop();

void gsm_setup() {
  Serial.begin(115200);
  mySerial.begin(57600,SERIAL_8N1,3,1);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Initializing...");
  mySerial.begin(115200);
  delay(1000);

  //call();
  //delay(15000);

  //message();
}

void gsm_loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void call(){
  mySerial.println("AT");
  delay(1000);
  mySerial.println("ATD+94761776047;"); // Replace with your p
}

void message(){
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+94761776047\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(1000);
  mySerial.print("Unauthorized Entry..!!"); //text content
  delay(1000);
  mySerial.write(26);
}

