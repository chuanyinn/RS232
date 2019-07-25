#include <AltSoftSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

AltSoftSerial altSerial;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(19200);
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(19200);

  // initialize the LCD
  lcd.begin();  
  // Turn on the blacklight and print a message.
  lcd.backlight();
  //lcd.print("LCD is ready");
}

//create a function that can collect the buffer
  // cast (char) from altSerial.read() to convert ASCII
  // Serial can only print string
void getArray(String *myArray, int myLength) {
  for (int counter = myLength; counter > 0; counter--) {
    *myArray = *myArray + (char)altSerial.read();
  }
  Serial.print(*myArray);
}

void loop() {
  // send
  altSerial.write(":FETCh:WAVelength? \n");
  delay(10);
  // receive
  String myBuffer = String();
  getArray(&myBuffer, altSerial.available());
  lcd.print(myBuffer);
  delay(500);
  lcd.clear();

}
