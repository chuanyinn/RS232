#include <SoftwareSerial.h>
#include <Wire.h> 
 
SoftwareSerial mySerial(5, 4); //232_TX,232_RX

char receivedChar;
boolean newData = false;

void setup()
{
    // Open serial communications and wait for port to open:
    
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    Serial.println("<Arduino is ready>");
    
    /*
    Serial.println(":MEAS:WAV?");
    Serial.write(":MEAS:WAV?");
    Serial.write(":FETC:WAV?");
    Serial.write(":READ:WAV?");
    Serial.write(":SYST:VERS?");
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    */
    // set the data rate for the SoftwareSerial port
    mySerial.begin(9600);
    
    mySerial.write("*IDN?");
    mySerial.write(":DISP:UNIT:POW DBM");
    //a simple write command

    /*
    int bytesSent = mySerial.write("8");
    //val = Serial.read();
    Serial.println(bytesSent);
    int byteRec = mySerial.read();
    Serial.println(byteRec);*/
    
}


void recvOneChar() {
    if (mySerial.available() > 0) {
        receivedChar = mySerial.read();
        newData = true;
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChar);
        newData = false;
    }
}

void loop(){
    recvOneChar();
    showNewData();
    //send a string to mySerial port
    //receive a number from mySerial port
}
