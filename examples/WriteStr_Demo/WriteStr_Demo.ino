/**********************************************************************************
 * Write String Test - Demo application
 * This demo simply illustrates the various ways you can now send data to a String 
 * object in ViSi-Genie, from an Arduino.
 * 
 * Demo uses Hardware Serial0 to communicate with the 4D Systems display module.
 * Simply create a Workshop4 Genie application for your 4D Systems display module, 
 * and place a 'Strings' object on the display, and download it to your module.
 * 
 * PLEASE NOTE: If you are using a non-AVR Arduino, such as a Due, or other variants
 * such as a Chipkit or Teensy, then you will need to comment out the Flash String 
 * line below - Line 60, as it will prevent the demo from compiling.
 */

#include <genieArduino.h>

Genie genie;

#define RESETLINE 4  // Change this if you are not using an Arduino Adaptor Shield Version 2 (see code below)

// Setup function
void setup()
{
  // NOTE, the genieBegin function (e.g. genieBegin(GENIE_SERIAL_0, 115200)) no longer exists.  
  // Use a Serial Begin and serial port of your choice in your code and use the genie.Begin function to send 
  // it to the Genie library (see this example below)
  // max of 200K Baud is good for most Arduinos. Galileo should use 115200 or below.  
  Serial.begin(9600);  // Serial0 @ 9600 Baud
  genie.Begin(Serial);   // Use Serial0 for talking to the Genie Library, and to the 4D Systems display
  
  // Reset the Display (change D4 to D2 if you have original 4D Arduino Adaptor)
  // THIS IS IMPORTANT AND CAN PREVENT OUT OF SYNC ISSUES, SLOW SPEED RESPONSE ETC
  // If NOT using a 4D Arduino Adaptor, digitalWrites must be reversed as Display Reset is Active Low, and
  // the 4D Arduino Adaptors invert this signal so must be Active High.  
  pinMode(RESETLINE, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(RESETLINE, 1);  // Reset the Display via D4
  delay(100);
  digitalWrite(RESETLINE, 0);  // unReset the Display via D4

  delay (3500); //let the display start up after the reset (This is important)
}

// Main loop
void loop()
{
  //An optional third parameter specifies the base (format) to use; permitted values are BIN (binary, or base 2), OCT (octal, or base 8), DEC (decimal, or base 10), HEX (hexadecimal, or base 16). 
  //For floating point numbers, this parameter specifies the number of decimal places to use.
  int x = -78;
  long y = 171;
  double z = 175.3456;
  int digits = 3;
  String Str = "This is string class";
  genie.WriteStr(0, "TEST");
  delay(1000);
  genie.WriteStr(0, z, digits); //3 decimal places
  delay(1000);
  genie.WriteStr(0, 123.45678, 5); // 5 decimal places
  delay(1000);
  genie.WriteStr(0, 123.45678); // 2 decimal places by default if no value is given to decimal place.
  delay(1000);
  genie.WriteStr(0, F("This string will be \n stored in flash memory")); // For AVR Arduinos only - Needs to be commented out for Due, Chipkit, Teensy etc.
  delay(1000);
  genie.WriteStr(0, "                                                        "); // Clear
  delay(10);
  genie.WriteStr(0, x); //prints negative integer
  delay(1000);
  genie.WriteStr(0, y);
  delay(1000);
  genie.WriteStr(0, -x, BIN); //base 2 of 78
  delay(1000);
  genie.WriteStr(0, y,16); //base 16
  delay(1000);
  genie.WriteStr(0, 10); //base 10 by default
  delay(1000);
  genie.WriteStr(0, 10,8); //base 8
  delay(1000);
  genie.WriteStr(0, Str); //prints String Class
  delay(1000);
  unsigned int zc = 123 ;
  genie.WriteStr(0, zc); //prints unsigned ints
  delay(1000);
  unsigned long e = 1234 ;
  genie.WriteStr(0, e); //prints unsigned long
  delay(1000);
}


