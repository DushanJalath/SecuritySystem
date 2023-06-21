#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include "gsm.h"

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)

// pin #RX2 is IN from sensor (YELLOW wire)
// pin #TX2 is OUT from arduino  (WHITE wire)

HardwareSerial mySerial(1);

#else
#define mySerial Serial1
#endif

int fprintx[3];
uint8_t count = 0;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  Serial.begin(115200);
  while (!Serial); 
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  mySerial.begin(57600, SERIAL_8N1, 16, 17);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();

  //////////////// GSM SetUp

  gsm_setup();

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}

void loop()
{

  ////////// GSM Loop
  gsm_loop();


  uint8_t warn = 0;
  int var;
  uint8_t j;
  bool duplicate;
  
  while (count < 3) {
    duplicate = false;
    
    var = getFingerprintIDez();
    
    j = 0;
    while (j < count) {
      if (var == fprintx[j]) {
        duplicate = true;
        break;
      }
      j++;
    }
    
    if ((var != -1) && (duplicate == false)) {
      fprintx[count] = var;
      count++;
    }

    if (warn > 20) {
      // (send SMS)-warn!!!
    }

    warn++;
  }
  
  if (count == 3) {
    Serial.println("Access Granted!!!");
    call();
    delay(15000);
    message();
    count++;
    delay(500);
  }
  
  delay(5000);           
}


// returns -1 if failed, otherwise returns ID #

int getFingerprintIDez() {
  
  uint8_t p = finger.getImage();
  
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  
  return finger.fingerID;
}