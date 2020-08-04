![image](http://www.4dsystems.com.au/downloads/4DLogo.png)

ViSi-Genie-Arduino-Library (A.K.A genieArduino)
==============================================================

Arduino Library for 4D Systems ViSi-Genie Environment

This library supports the following:
Support for neagative numbers, unsigned longs, unsigned integers with the WriteStr function.
Features enhanced String Writing capability, no longer is a character Array the only viable option. 
Support for Workshop4 PRO features.
2+ displays connected to a single Arduino, and adds a Demo to illustrate how that is achieved.
New Internal and Inherent Widgets.
Much more...

## Information

This library provides high level functions for the Arduino, to ease communication with 4D Systems modules when using the module configured with ViSi-Genie.
Workshop4 PRO adds additional features to ViSi-Genie, allowing the User to write 4DGL code which can be executed at will from ViSi-Genie, enabling many advanced features not previously possible.
Please refer to the 4D Systems website, namingly the Workshop4 Product Page, for documentation regarding Workshop4, and its environments.

## Installation

Library folder should be placed in the C:\Users\(User name)\My Documents\Arduino\Libraries\ folder, or equivalent. (restart the IDE if already open).

PLEASE ensure that the old library (if installed) has been removed completely so it does not conflict.

For more information on the installation, please refer to [Installing Additional Arduino Libraries] (http://arduino.cc/en/Guide/Libraries)

Open the ViSi-Genie project using Workshop4 and download to your display, connect the display to Arduino, reset the Arduino and it should work.

This library should be discoverable from the Arduino IDE Library Manager too.

## Example Sketch

Inside the library are 4 example sketches, to assist with getting started using this library. Inside is also a ViSi-Genie Workshop4 project, which can be used on a range of 4D Systems displays (designed on a uLCD-32PTU however can be changed via Workshop4 menu). It illustrates how to use some of the commands in the library include Read Object, Write Object, Reported Messages, Write Contrast and Write String.

## Tested with

This library has been tested on the Duemilanove, Uno, Mega 1280, Mega 2560, Leonardo, Chipkit Max32, Due, Intel Galileo, Teensy and Yun (Software Serial only on Yun). 
Any problems discovered with this library, please contact technical support so fixes can be put in place, or seek support from our forum.

## Compatible 4D Systems Display Modules

This library will work with all 4D Systems Modules which are capable of using the ViSi-Genie environment. This is therefore all Picaso, Pixxi-28, Pixxi-44 and Diablo16 Display Modules.
The demo included with this library was made for the gen4-uLCD-32DCT-CLB (3.2" Capacitive Touch gen4 module) however can easily be adapted to other size displays.

## General Library Discussion
-----------------------------

This section serves to give brief discussion about the constructor and functions included in the library. For functional examples on how to use these functions in a project, refer to the examples folder.

### Genie()
This is the constructor for the library. It creates a unique instance that can be set to use the desired serial port.

    Genie genie; // Creates a new instance named 'genie'

### Begin(Stream &serial)
Creates an instance of ViSi Genie by assigning a *serial* stream


| Parameters | Description |
|:----------:| ----------- |
| serial     | Stream object that represents the UART hardware |

    Serial.begin(115200); // Open Serial @115200. Can use other Serial UART's (Serial1, Serial2...) depending on your Arduino.
    genie.Begin(Serial);  // Sets Serial/Serial0 to be used by the Genie instance 'genie'

### WriteContrast(uint16_t value)
Sets the display contrast/brightness to a new *value*

| Parameters | Description |
|:----------:| ----------- |
| value      | New brightness/contrast value. The range of this value depends on the 4D display, Typically 0-15 Range |

    genie.WriteContrast(0); // Sets the contrast/brightness value to 0, effectively turning off the backlight
    genie.WriteContrast(10); // Sets the contrast/brightness value to 10, about 2/3 max brightness

### ReadObject(uint16_t object, uint16_t index)
Sends a request to read the value of the widget specified by *object* (ex: GENIE_OBJ_GAUGE) and *index*. The value will be sent as a GENIE_REPORT_OBJECT command.
A full list of available objects (ex: GENIE_OBJ_GAUGE, GENIE_OBJ_SLIDER etc) can be found at the bottom of this Readme.

| Parameters | Description |
|:----------:| ----------- |
| object     | Type of target widget |
| index      | Index number of target widget |

    genie.ReadObject(GENIE_OBJ_GAUGE, 0); // Request a report of the widget Gauge0

### WriteObject(uint16_t object, uint16_t index, uint16_t data)
Updates the widget, specified by *object* (ex: GENIE_OBJ_GAUGE) and *index*, to a new value specified by *data*
A full list of available objects (ex: GENIE_OBJ_GAUGE, GENIE_OBJ_SLIDER etc) can be found at the bottom of this Readme.

| Parameters | Description |
|:----------:| ----------- |
| object     | Type of target widget |
| index      | Index number of target widget |
| data       | New value for the target widget |

    genie.WriteObject(GENIE_OBJ_GAUGE, 0, 50); // Sets Gauge0 to 50

### WriteIntLedDigits(uint16_t index, int16_t data)
Updates the Internal LedDigits specified by *index* to a new 16-bit value, specified by *data*. The widget parameter *Format* in ViSi Genie project should be set to Int16. Internal LedDigits are availble for Diablo and Pixxi displays.

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Internal LedDigits |
| data       | New 16-bit integer value for the target Internal LedDigits |

    genie.WriteIntLedDigits(0, 50); // Sets ILedDigits0 to 50

### WriteIntLedDigits(uint16_t index, float data)
Updates the Internal LedDigits specified by *index* to a new 32-bit float value, specified by *data*. The widget parameter *Format* in ViSi Genie project should be set to any Float option. Internal LedDigits are availble for Diablo and Pixxi displays.

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Internal LedDigits |
| data       | New 32-bit float value for the target Internal LedDigits |

    genie.WriteIntLedDigits(0, 3.1416f); // Sets ILedDigits0 to 3.1416

### WriteIntLedDigits(uint16_t index, int32_t data)
Updates the Internal LedDigits specified by *index* to a new 32-bit integer value, specified by *data*. The widget parameter *Format* in ViSi Genie project should be set to Int16. Internal LedDigits are availble for Diablo and Pixxi displays.

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Internal LedDigits |
| data       | New 32-bit integer value for the target Internal LedDigits |

    genie.WriteIntLedDigits(0, 1000000L); // Sets ILedDigits0 to 1000000

### WriteStr(uint16_t index, char * string)
Updates the String widget specified by *index* with a new character string specified by *string*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| string     | Character pointer containing the text to print in the String widget |

    genie.WriteStr(0, "Sample String"); // Set text in String0 to "Sample String"

### WriteStr(uint16_t index, const __FlashStringHelper *ifsh)
Updates the String widget specified by *index* with a string stored in program space (flash memory) specified by *ifsh*. This is only available for AVR boards.

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| ifsh       | Flash string containing the text to print in the String widget |

    // Writes the string stored in flash memory to String1
	genie.WriteStr(1, F("Hello from Flash Memory")); // For AVR Arduinos only
                                                    
### WriteStr(uint16_t index, const String &s)
Updates the String widget specified by *index* with a String widget specified by *s*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| s          | String object containing the text to print in the String widget |

    String str = "This is string class";
    genie.WriteStr(0, Str); // Writes the String class 'str' to String0

### WriteStrU(uint16_t index, uint16_t * string)
Updates the String widget specified by *index* with a new Unicode (16-bit) character string specified by *string*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| string     | Character pointer containing the text to print in the String widget |

    uint16_t * unistr = {0x0034, 0x0044, 0x0020, 0x30B7, 0x30B9, 0x30C6, 0x30E0, 0x30BA, 0};
    genie.WriteStr(2, unistr); // Writes the Unicode string "4D システムズ" to String2

### WriteStr(uint16_t index, int n)
Updates the String widget specified by *index* with a new integer value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Signed short integer value that will be formatted with base 10 to a string and will be printed in the String widget |

    genie.WriteStr(0, 10000); // Writes the value 10000 to String0

### WriteStr(uint16_t index, int n, int base)
Updates the String widget specified by *index* with a new integer value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Signed short integer value that will be formatted to a string and will be printed in the String widget |
| base       | Custom base to used when formatting the value to a string |

    genie.WriteStr(4, 10000, 16); // Writes the value 10000 to String4 in hexadecimal

### WriteStr(uint16_t index, unsigned int n)
Updates the String widget specified by *index* with a new unsigned integer value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Unsigned short integer value that will be formatted with base 10 to a string and will be printed in the String widget |

    unsigned int value = 40000;
    genie.WriteStr(2, value); // Writes the value 40000 to String2

### WriteStr(uint16_t index, unsigned int n, int base)
Updates the String widget specified by *index* with a new unsigned integer value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Unsigned short integer value that will be formatted to a string and will be printed in the String widget |
| base       | Custom base to used when formatting the value to a string |

    unsigned int value = 40000;
    genie.WriteStr(1, value, 16); // Writes the value 40000 to String1 in hexadecimal

### WriteStr(uint16_t index, long n)
Updates the String widget specified by *index* with a new long value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Signed long integer value that will be formatted with base 10 to a string and will be printed in the String widget |

    genie.WriteStr(2, 100000L); // Writes the value 100000 to String2

### WriteStr(uint16_t index, long n, int base)
Updates the String widget specified by *index* with a new long value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Signed long integer value that will be formatted to a string and will be printed in the String widget |
| base       | Custom base to used when formatting the value to a string |

    genie.WriteStr(3, 100000L, 8); // Writes the value 100000 to String3 in octal

### WriteStr(uint16_t index, unsigned long n)
Updates the String widget specified by *index* with a new unsigned long value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Unsigned long integer value that will be formatted with base 10 to a string and will be printed in the String widget |

    genie.WriteStr(0, 3000000000UL); // Writes the value 3000000000 to String0

### WriteStr(uint16_t index, unsigned long n, int base)
Updates the String widget specified by *index* with a new unsigned long value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Unsigned long integer value that will be formatted to a string and will be printed in the String widget |
| base       | Custom base to used when formatting the value to a string |

    genie.WriteStr(1, 3000000000UL, 16); // Writes the value 3000000000 to String1 in hexadecimal

### WriteStr(uint16_t index, double n)
Updates the String widget specified by *index* with a new 64-bit float value *n* with 2 decimal digits

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Signed 64-bit float value that will be formatted to a string with 2 decimal places (default) and will be printed in the String widget |

    double value = 175.3456;
    genie.WriteStr(0, value); // Writes the 64-bit float value 175.3456 to String0
                              // with 2 decimal places (175.34)

### WriteStr(uint16_t index, double n, digits)
Updates the String widget specified by *index* with a new 64-bit float value *n* with the number of decimal digits as specified by *digits*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target String |
| n          | Signed 64-bit float value that will be formatted to a string and will be printed in the String widget |
| digits     | Number of decimal places to format the value with |

    double value = 175.3456;
    genie.WriteStr(0, value, 4); // Writes the 64-bit float value 175.3456 to String0
								 // with 4 decimal places (175.3456)
								 
### WriteInhLabel(uint16_t index)
Updates the Inherent Label widget specified by *index* with the default contents defined in Workshop4

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |

    genie.WriteInhLabel(1); // Set text in ILabelB1 to default String
	
### WriteInhLabel(uint16_t index, char * string)
Updates the Inherent Label widget specified by *index* with a new character string specified by *string*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| string     | Character pointer containing the text to print in the Inherent Label widget |

    genie.WriteInhLabel(0, "Sample String"); // Set text in ILabelB0 to "Sample String"

### WriteInhLabel(uint16_t index, const __FlashStringHelper *ifsh)
Updates the Inherent Label widget specified by *index* with a string stored in program space (flash memory) specified by *ifsh*. This is only available for AVR boards.

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| ifsh       | Flash string containing the text to print in the Inherent Label widget |

    // Writes the string stored in flash memory to ILabelB1
    genie.WriteInhLabel(1, F("Hello from Flash Memory")); // For AVR Arduinos only

### WriteInhLabel(uint16_t index, const String &s)
Updates the Inherent Label widget specified by *index* with a Inherent Label widget specified by *s*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| s          | String object containing the text to print in the Inherent Label widget |

    String str = "This is string class";
    genie.WriteInhLabel(0, Str); // Writes the String class 'str' to ILabelB0

### WriteInhLabel(uint16_t index, int n)
Updates the Inherent Label widget specified by *index* with a new integer value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Signed short integer value that will be formatted with base 10 to a string and will be printed in the Inherent Label widget |

    genie.WriteInhLabel(0, 10000); // Writes the value 10000 to ILabelB0

### WriteInhLabel(uint16_t index, int n, int base)
Updates the Inherent Label widget specified by *index* with a new integer value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Signed short integer value that will be formatted to a string and will be printed in the Inherent Label widget |
| base       | Custom base to used when formatting the value to a string |

    // Writes the value 10000 to ILabelB4 in hexadecimal
    genie.WriteInhLabel(4, 10000, 16); 

### WriteInhLabel(uint16_t index, unsigned int n)
Updates the Inherent Label widget specified by *index* with a new unsigned integer value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Unsigned short integer value that will be formatted with base 10 to a string and will be printed in the Inherent Label widget |

    unsigned int value = 40000;
    genie.WriteInhLabel(2, value); // Writes the value 40000 to ILabelB2

### WriteInhLabel(uint16_t index, unsigned int n, int base)
Updates the Inherent Label widget specified by *index* with a new unsigned integer value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Unsigned short integer value that will be formatted to a string and will be printed in the Inherent Label widget |
| base       | Custom base to used when formatting the value to a string |

    unsigned int value = 40000;
    // Writes the value 40000 to ILabelB1 in hexadecimal
    genie.WriteInhLabel(1, value, 16); 

### WriteInhLabel(uint16_t index, long n)
Updates the Inherent Label widget specified by *index* with a new long value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Signed long integer value that will be formatted with base 10 to a string and will be printed in the Inherent Label widget |

    genie.WriteInhLabel(2, 100000L); // Writes the value 100000 to ILabelB2

### WriteInhLabel(uint16_t index, long n, int base)
Updates the Inherent Label widget specified by *index* with a new long value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Signed long integer value that will be formatted to a string and will be printed in the Inherent Label widget |
| base       | Custom base to used when formatting the value to a string |

    // Writes the value 100000 to ILabelB3 in octal
    genie.WriteInhLabel(3, 100000L, 8); 

### WriteInhLabel(uint16_t index, unsigned long n)
Updates the Inherent Label widget specified by *index* with a new unsigned long value *n* with base 10

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Unsigned long integer value that will be formatted with base 10 to a string and will be printed in the Inherent Label widget |

    genie.WriteInhLabel(0, 3000000000UL); // Writes the value 3000000000 to ILabelB0

### WriteInhLabel(uint16_t index, unsigned long n, int base)
Updates the Inherent Label widget specified by *index* with a new unsigned long value *n* with base specified by *base*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Unsigned long integer value that will be formatted to a string and will be printed in the Inherent Label widget |
| base       | Custom base to used when formatting the value to a string |

    // Writes the value 3000000000 to ILabelB1 in hexadecimal
    genie.WriteInhLabel(1, 3000000000UL, 16); 

### WriteInhLabel(uint16_t index, double n)
Updates the Inherent Label widget specified by *index* with a new 64-bit float value *n* with 2 decimal digits

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Signed 64-bit float value that will be formatted to a string with 2 decimal places and will be printed in the Inherent Label widget |

    double value = 175.3456;
    // Writes the 64-bit float value 175.3456 to ILabelB0
    genie.WriteInhLabel(0, value); // with 2 decimal places (175.34)

### WriteInhLabel(uint16_t index, double n, digits)
Updates the Inherent Label widget specified by *index* with a new 64-bit float value *n* with the number of decimal digits as specified by *digits*

| Parameters | Description |
|:----------:| ----------- |
| index      | Index number of target Inherent Label |
| n          | Signed 64-bit float value that will be formatted to a string and will be printed in the Inherent Label widget |
| digits     | Number of decimal places to format the value with |

    double value = 175.3456;
    // Writes the 64-bit float value 175.3456 to ILabelB0 
    genie.WriteInhLabel(0, value, 4); // with 4 decimal places (175.3456)

### AttachEventHandler(UserEventHandlerPtr userHandler)
Attach an event handler to handle messages from the display (ex. GENIE_REPORT_EVENT and GENIE_REPORT_OBJECT). Ideally, the handler function doesn't do anything that blocks for a long period since this would cause the command handling to be delayed.
Please refer to the demos provided for more context of what this looks like when implemented.

| Parameters  | Description |
|:-----------:| ----------- |
| userHandler | Pointer to the handler function. The function should follow the format *void userHandler()* |

- Usage Example

      genie.AttachEventHandler(myGenieEventHandler); // Attach the event handler
                                                     // for processing messages

- Handler Function Example

      void myGenieEventHandler(void)
      {
          genieFrame Event; // Prepare a genie frame container
          genie.DequeueEvent(&Event); // Store next message from display to 'Event'

          // Process event here (quickly), see example below

          // Check if the message stored in 'Event' is a GENIE_REPORT_EVENT from  Slider0
          if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_SLIDER, 0))    
          {
              // Receive the event data from the Slider0
              slider_val = genie.GetEventData(&Event);
              // Write Slider0 value to LedDigits0
              genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0, slider_val);
          }          
      }

### DoEvents()
This handles all the receiving of messages from the display and therefore should run as frequent as possible. This also calls the event handlers attached using *AttachEventHandler*, *AttachMagicByteReader* and *AttachMagicDoubleByteReader*
This should be run in your main loop() or in a controlled function which runs as often as possible.

    void loop()
    {
        static long waitPeriod = millis();
        genie.DoEvents(); // Run as frequently as possible for best experience

        if (millis() >= waitPeriod)
        {
            // Update the display here

            // Ensure that this code block only runs after ~100ms
            waitPeriod = millis() + 100;
        }
    }

### EventIs(genieFrame * e, uint8_t cmd, uint8_t object, uint8_t index)
Returns true if the command stored in genieFrame *e* matches the criteria specified by *cmd*, *object* and *index*. Otherwise, returns false.

| Parameters  | Description |
|:-----------:| ----------- |
| e           | Pointer to a genieFrame structure that specifies where the event under evaluation is stored |
| cmd         | Specifies the type of command expected of the message |
| object      | Specifies the type of widget from which the event is from |
| index       | Specifies the index of widget from which the event is from |

    // Check if the message stored in 'Event' is a GENIE_REPORT_EVENT from Slider0
    if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_SLIDER, 0))    
    {
        // Receive the event data from the Slider0
        slider_val = genie.GetEventData(&Event);
        // Write Slider0 value to LedDigits0
        genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0, slider_val);
    }

### DequeueEvent(genieFrame * buff)
Remove the next message from the queue and store it to genieFrame *buff*. This function should be used inside the custom event handler.

| Parameters  | Description |
|:-----------:| ----------- |
| buff        | Pointer to a genieFrame structure that specifies where the next event should be stored |

See *AttachEventHandler* for an example.

### GetEventData(genieFrame * e)
Retrieves the 16-bit value from genieFrame *e*

| Parameters  | Description |
|:-----------:| ----------- |
| buff        | Pointer to a genieFrame structure that specifies where the data to read is from |

See *AttachEventHandler* for an example.

## ViSi Genie Pro Library Discussion
------------------------------------

### AttachMagicByteReader(UserBytePtr userHandler)
Attach an event handler to handle magic bytes from the display. Magic Bytes needs to be programmed using Magic features (ex. MagicTouch, MagicRelease, etc.) of ViSi Genie.

It is suggested to store the data and process them later on to prevent a blocking delay.

| Parameters  | Description |
|:-----------:| ----------- |
| userHandler | Pointer to the handler function. The function should follow the format *void UserBytePtr(uint8_t, uint8_t)* |

- Usage Example

      // Attach the event handler for processing magic bytes
      genie.AttachMagicByteReader(myMagicByteHandler);

- Handler Function Example

      byte buffer0[255]; // Temporary buffer 0 to store the magic bytes
      byte buffer1[255]; // Temporary buffer 1 to store the magic bytes

      void myMagicByteHandler(uint8_t index, uint8_t len)
      {
          // If the magic bytes is coming from MagicObject0
          if (index == 0) {
              // Store the data to buffer0
              for (int i = 0; i < len; i++) {
                  buffer0[i] = genie.GetNextByte();
              }
          }
          // If the magic bytes is coming from MagicObject1
          if (index == 1) {
              // Store the data to buffer1
              for (int i = 0; i < len; i++) {
                  buffer1[i] = genie.GetNextByte();
              }
          }
      }

### AttachMagicDoubleByteReader(UserDoubleBytePtr userHandler)
Attach an event handler to handle Magic Double Bytes from the display. Magic Double Bytes needs to be programmed using Magic features (ex. MagicTouch, MagicRelease, etc.) of ViSi Genie.

It is suggested to store the data and process them later on to prevent a blocking delay.

| Parameters  | Description |
|:-----------:| ----------- |
| userHandler | Pointer to the handler function. The function should follow the format *void UserBytePtr(uint8_t, uint8_t)* |

- Usage Example

      // Attach the event handler for processing magic double bytes
      genie.AttachMagicDoubleByteReader(myMagicDoubleByteHandler);

- Handler Function Example

      uint16_t buffer0[255]; // Temporary buffer 0 to store the magic double bytes
      uint16_t buffer1[255]; // Temporary buffer 1 to store the magic double bytes

      void myMagicDoubleByteHandler(uint8_t index, uint8_t len)
      {
          // If the magic double bytes is coming from MagicObject0
          if (index == 0) {
              // Store the data to buffer0
              for (int i = 0; i < len; i++) {
                  buffer0[i] = genie.GetNextDoubleByte();
              }
          }
          // If the magic double bytes is coming from MagicObject1
          if (index == 1) {
              // Store the data to buffer1
              for (int i = 0; i < len; i++) {                  
                  buffer1[i] = genie.GetNextDoubleByte();
              }
          }
      }

### GetNextByte()
This function can be utilized to receive next incoming byte from the display. This should be used when receiving magic bytes in the user byte handler.

See *AttachMagicByteReader* for an example.

### GetNextDoubleByte()
This function can be utilized to receive next two (2) incoming bytes from the display. This should be used when receiving magic double bytes in the user double byte handler.

See *AttachMagicDoubleByteReader* for an example.

### WriteMagicBytes(uint16_t index, uint8_t *bytes, uint16_t len)
Send magic *bytes* with size *len* to MagicObject specified by *index*. The specified MagicObject should be programmed to handle the magic bytes that will be sent by this function.

| Parameters  | Description |
|:-----------:| ----------- |
| index       | Index of MagicObject that is programmed to receive and process the data |
| bytes       | Pointer to a byte array that specifies where the data is stored|
| len         | Specifies the number of bytes to send |

    uint8_t bytes[] = {0x34, 0x44, 0x20, 0x53, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x73};
    genie.WriteMagicBytes(0, bytes, 10); // Writes 10 magic bytes to MagicObject0

### WriteMagicDBytes(uint16_t index, uint16_t *dbytes, uint16_t len)
Send magic * bytes* with size *len* to MagicObject specified by *index*. The specified MagicObject should be programmed to handle the magic bytes that will be sent by this function.

| Parameters  | Description |
|:-----------:| ----------- |
| index       | Index of MagicObject that is programmed to receive and process the data |
| dbytes      | Pointer to a 16-bit array that specifies where the data is stored|
| len         | Specifies the number of double bytes to send |

    uint16_t dbytes[] = {0x0034, 0x0044, 0x0020, 0x30B7, 0x30B9, 0x30C6, 0x30E0, 0x30BA};
    genie.WriteMagicDBytes(1, dbytes, 8); // Writes 8 magic double bytes to MagicObject1
	
## Available Library Object Types
---------------------------------

This section lists all of the objects/widgets that are available to be used by this library, which represent each of the widgets available to be placed using the Workshop4 IDE.

These object names are inserted into the ReadObject and WriteObject functions (listed above), and data received back from them presents itself in the AttachEventHandler function.

For more information on each of the actual Widgets in Workshop4, please refer to the Workshop4 Widgets Reference Manual - available on the Workshop4 Product page of the 4D Systems website.

| Object Name | Description |
| ----------- | ----------- |
| GENIE_OBJ_DIPSW	| Dip Switch Widget |
| GENIE_OBJ_KNOB	| Knob Widget |
| GENIE_OBJ_ROCKERSW	| Rocker Switch Widget |
| GENIE_OBJ_ROTARYSW	| Rotary Switch Widget |
| GENIE_OBJ_SLIDER	| Slider Widget |
| GENIE_OBJ_TRACKBAR	| Track Bar Widget |
| GENIE_OBJ_WINBUTTON	| Winbutton Widget |
| GENIE_OBJ_ANGULAR_METER	| Angular Meter Widget |
| GENIE_OBJ_COOL_GAUGE	| Cool Gauge Widget |
| GENIE_OBJ_CUSTOM_DIGITS	| Custom Digits Widget |
| GENIE_OBJ_FORM	| Form Widget |
| GENIE_OBJ_GAUGE	| Gauge Widget |
| GENIE_OBJ_IMAGE	| Image Widget |
| GENIE_OBJ_KEYBOARD	| Keyboard Widget |
| GENIE_OBJ_LED	| LED Widget |
| GENIE_OBJ_LED_DIGITS	| LED Digits Widget |
| GENIE_OBJ_METER	| Meter Widget |
| GENIE_OBJ_STRINGS	| String Widget |
| GENIE_OBJ_THERMOMETER	| Thermometer Widget |
| GENIE_OBJ_USER_LED	| User LED Widget |
| GENIE_OBJ_VIDEO	| Video Widget |
| GENIE_OBJ_STATIC_TEXT	| Static Text Widget |
| GENIE_OBJ_SOUND	| Sound Widget |
| GENIE_OBJ_TIMER	| Timer Widget |
| GENIE_OBJ_SPECTRUM	| Spectrum Widget |
| GENIE_OBJ_SCOPE	| Scope Widget |
| GENIE_OBJ_TANK	| Tank Widget |
| GENIE_OBJ_USERIMAGES	| User Images Widget |
| GENIE_OBJ_PINOUTPUT	| Pin Output Widget |
| GENIE_OBJ_PININPUT	| Pin Input Widget |
| GENIE_OBJ_4DBUTTON	| 4D Button Widget |
| GENIE_OBJ_ANIBUTTON	| Animated Button Widget |
| GENIE_OBJ_COLORPICKER	| Colour Picker Widget |
| GENIE_OBJ_USERBUTTON	| User Button Widget |
| GENIE_OBJ_SMARTGAUGE	| Smart Gauge Widget (PRO Only) |
| GENIE_OBJ_SMARTSLIDER	| Smart Slider Widget (PRO Only) |
| GENIE_OBJ_SMARTKNOB	| Smart Knob Widget (PRO Only) | 
| GENIE_OBJ_ILED_DIGITS_H	| Internal LED Digits Widget - High Byte |
| GENIE_OBJ_ILED_DIGITS_L	| Internal LED Digits Widget - Low Byte |
| GENIE_OBJ_IANGULAR_METER	| Internal Angular Meter Widget |
| GENIE_OBJ_IGAUGE	| Internal Gauge Widget |
| GENIE_OBJ_ILED	| Internal LED Widget |
| GENIE_OBJ_INEEDLE	| Internal Needle Widget |
| GENIE_OBJ_IRULER	| Internal Ruler Widget |
| GENIE_OBJ_ILED_DIGIT	| Internal LED Digit Widget |
| GENIE_OBJ_ILED_DIGITS	| Internal LED Digits Widget |
| GENIE_OBJ_IBUTTOND	| Internal Button D Widget |
| GENIE_OBJ_IDIAL	| Internal Dial Widget |
| GENIE_OBJ_ISWITCH	| Internal Switch Widget |
| GENIE_OBJ_ISLIDERE	| Internal Slider E Widget |
| GENIE_OBJ_IBUTTONE	| Inherent Button E Widget |
| GENIE_OBJ_ITOGGLE_INPUT	| Inherent Toggle Input Widget |
| GENIE_OBJ_ILABELB	| Inherent Label B Widget |
| GENIE_OBJ_IUSER_GAUGE	| Inherent User Gauge Widget |
| GENIE_OBJ_IMEDIA_BUTTON	| Inherent Media Button Widget |
| GENIE_OBJ_IMEDIA_GAUGE	| Inherent Media Gauge Widget |
| GENIE_OBJ_IMEDIA_THERMOMETER	| Inherent Media Thermometer Widget |
| GENIE_OBJ_IMEDIA_ROTARY	| Inherent Media Rotary Widget |
| GENIE_OBJ_IMEDIA_LED	| Inherent Media LED Widget |
| GENIE_OBJ_IMEDIA_SLIDER	| Inherent Media Slider Widget |
| GENIE_OBJ_IROTARY_INPUT	| Inherent Rotary Input Widget |
| GENIE_OBJ_ISWITCHB	| Inherent Switch B Widget |
| GENIE_OBJ_ISLIDERH	| Inherent Slider H Widget |
| GENIE_OBJ_ISLIDERG	| Inherent Slider G Widget |
| GENIE_OBJ_ISLIDERF	| Inherent Slider F Widget |
| GENIE_OBJ_ISLIDERD	| Inherent Slider D Widget |
| GENIE_OBJ_ISLIDERC	| Inherent Slider C Widget |
| GENIE_OBJ_ILINEAR_INPUT	| Inherent Linear Input Widget |

## Questions/Issues?

Please sign up for our Forum and ask a question there, or submit a Tech Support Ticket from our website.
http://forum.4dsystems.com.au or http://www.4dsystems.com.au/support
Feel free to add a Github issue if you find a problem, we will do our best to help solve the problem.
