#include <SoftwareSerial.h>
#include <Wire.h> 

SoftwareSerial mySerial(5, 6); //232_TX,232_RX, seen from pinout of RS232 shield
//this could be flipped

void setup()
{
    // Open serial communications and wait for port to open:
    
    Serial.begin(19200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    Serial.println("<Arduino is ready>");
    
    // set the data rate for the SoftwareSerial port
    mySerial.begin(19200);

    mySerial.write("*IDN?\n");
    Serial.println(mySerial.available());
    Serial.println(Serial.available());
}


void loop(){
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

}
