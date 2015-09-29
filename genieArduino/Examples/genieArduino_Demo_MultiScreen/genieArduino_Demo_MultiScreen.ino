#include <genieArduino.h>

// This Demo extends the genieArduino_Demo, by showing how to use more than 1 screen at a time, attached to an Arduino with 2+ Serial Ports.
// This Demo uses the same WS4 Genie program on both displays, in this case, 2x uLCD-32PTU's, and an Arduino Mega.
// NOTE: Both displays must be connected for this demo to function.

// This Demo communicates with 2 4D Systems Displays, configured with ViSi-Genie, utilising the Genie Arduino Library - https://github.com/4dsystems/ViSi-Genie-Arduino-Library.
// The display demo has a slider, a cool gauge, an LED Digits, a string box and a User LED.
// The program receives messages from the Slider0 object on each display using the Reported Events. This is triggered each time the Slider changes on the display, and an event
// is genereated and sent automatically. Reported Events originate from the On-Changed event from the slider itself, set in the Workshop4 software.
// Coolgauge is written to using Write Object, and the String is updated using the Write String command, showing the version of the library.
// The User LED is updated by the Arduino, by first doing a manual read of the User LED and then toggling it based on the state received back.

// As the slider changes, it sends its value to the Arduino (Arduino also polls its value using genie.ReadObject, as above), and the Arduino then
// tells the LED Digit to update its value using genie.WriteObject, but of the other displays LED Digit! So the Slider message goes via the Arduino to the LED Digit
// of the other display.
// Coolgauge is updated via simple timer in the Arduino code, and updates the display with its value.
// The User LED is read using genie.ReadObject, and then updated using genie.WriteObject. It is manually read, it does not use an Event.

// This demo illustrates how to use genie.ReadObject, genie.WriteObject, Reported Messages (Events), genie.WriteStr, genie.WriteContrast, plus supporting functions.

// Application Notes on the 4D Systems Website that are useful to understand this library are found: http://www.4dsystems.com.au/appnotes 
// Good App Notes to read are: 
// ViSi-Genie Connecting a 4D Display to an Arduino Host - http://www.4dsystems.com.au/appnote/4D-AN-00017/
// ViSi-Genie Writing to Genie Objects Using an Arduino Host - http://www.4dsystems.com.au/appnote/4D-AN-00018/
// ViSi-Genie A Simple Digital Voltmeter Application using an Arduino Host - http://www.4dsystems.com.au/appnote/4D-AN-00019/
// ViSi-Genie Connection to an Arduino Host with RGB LED Control - http://www.4dsystems.com.au/appnote/4D-AN-00010/
// ViSi-Genie Displaying Temperature values from an Arduino Host - http://www.4dsystems.com.au/appnote/4D-AN-00015/
// ViSi-Genie Arduino Danger Shield - http://www.4dsystems.com.au/appnote/4D-AN-00025/

Genie display1; // Genie Display 1
Genie display2; // Genie Display 2
#define RESETLINE1 4  // Reset pin attached to Display 1
#define RESETLINE2 2  // Reset pin attached to Display 2

void setup()
{
  // Use a Serial Begin and serial port of your choice in your code and use the genie.Begin function to send 
  // it to the Genie library (see this example below)
  // 200K Baud is good for most Arduinos. Galileo should use 115200. 
  
  Serial.begin(200000);   // Serial0 @ 200000 (200K) Baud
  display1.Begin(Serial);   // Use Serial0 for talking to the Genie Library, and to the 4D Systems display #1
  
  Serial1.begin(200000);  // Serial1 @ 200000 (200K) Baud
  display2.Begin(Serial1);  // Use Serial1 for talking to the Genie Library, and to the 4D Systems display #2

  display1.AttachEventHandler(myGenieEventHandler1); // Attach the user function Event Handler for processing events for display 1
  display2.AttachEventHandler(myGenieEventHandler2); // Attach the user function Event Handler for processing events for display 2
  
  // Reset the Displays
  // THIS IS IMPORTANT AND CAN PREVENT OUT OF SYNC ISSUES, SLOW SPEED RESPONSE ETC 
  pinMode(RESETLINE1, OUTPUT);  // Set D4 on Arduino to Output to control the reset line to Display 1
  pinMode(RESETLINE2, OUTPUT);  // Set D2 on Arduino to Output to control the reset line to Display 2
  digitalWrite(RESETLINE1, 1);  // Reset Display 1
  digitalWrite(RESETLINE2, 1);  // Reset Display 2
  delay(100);
  digitalWrite(RESETLINE1, 0);  // unReset Display 1
  digitalWrite(RESETLINE2, 0);  // unReset Display 2

  delay (3500); //let the display start up after the reset (This is important)

  //Set the brightness/Contrast of the Display - (Not needed but illustrates how) 
  //Most Displays, 1 = Display ON, 0 = Display OFF
  //For uLCD-43, uLCD-220RD, uLCD-70DT, and uLCD-35DT, use 0-15 for Brightness Control, where 0 = Display OFF, though to 15 = Max Brightness ON.
  display1.WriteContrast(1); // Display ON
  display2.WriteContrast(1); // Display ON
  
  //Write a string to the Display to identify each display 
  display1.WriteStr(0, "Hello Display 1");
  display2.WriteStr(0, "Hello Display 2");
}

void loop()
{
  static long waitPeriod = millis(); // Time now
  
  static int gaugeAddVal1 = 1; // Set the value at which the Gauge on Display 1 increases by initially
  static int gaugeVal1 = 10; // Starting Value for Gauge on Display 1
  static int gaugeAddVal2 = 2; // Set the value at which the Gauge on Display 2 increases by initially
  static int gaugeVal2 = 50; // Starting Value for Gauge on Display 2

  display1.DoEvents(); // This calls the library each loop to process the queued responses from display 1
  display2.DoEvents(); // This calls the library each loop to process the queued responses from display 2

  if (millis() >= waitPeriod)
  {
    // Write to CoolGauge0 with the value in the gaugeVal variable on Display 1
    display1.WriteObject(GENIE_OBJ_COOL_GAUGE, 0, gaugeVal1);
    
    // Simulation code for Gauge on Display 1, just to increment and decrement gauge value each loop, for animation
    gaugeVal1 += gaugeAddVal1;
    if (gaugeVal1 >= 99) gaugeAddVal1 = -1; // If the value is > or = to 99, make gauge decrease in value by 1
    if (gaugeVal1 <= 0) gaugeAddVal1 = 1; // If the value is < or = to 0, make gauge increase in value by 1

    // The results of this call will be available to myGenieEventHandler() after the display has responded
    // Do a manual read from the UserLEd0 object on Display 1
    display1.ReadObject(GENIE_OBJ_USER_LED, 0);
    
    // Write to CoolGauge0 with the value in the gaugeVal variable on Display 2
    display2.WriteObject(GENIE_OBJ_COOL_GAUGE, 0, gaugeVal2);
    
    // Simulation code for Gauge on Display 2, just to increment and decrement gauge value each loop, for animation
    gaugeVal2 += gaugeAddVal2;
    if (gaugeVal2 >= 99) gaugeAddVal2 = -2; // If the value is > or = to 99, make gauge decrease in value by 2
    if (gaugeVal2 <= 0) gaugeAddVal2 = 2; // If the value is < or = to 0, make gauge increase in value by 2

    // The results of this call will be available to myGenieEventHandler() after the display has responded
    // Do a manual read from the UserLed0 object on Display 2
    display2.ReadObject(GENIE_OBJ_USER_LED, 0);

    waitPeriod = millis() + 50; // rerun this code to update Cool Gauge and Slider in another 50ms time.
  }
}

/////////////////////////////////////////////////////////////////////
//
// This is the user's event handler. It is called by the DoEvents()
// when the following conditions are true
//
//		The link is in an IDLE state, and
//		There is an event to handle
//
// The event can be either a REPORT_EVENT frame sent asynchronously
// from the display or a REPORT_OBJ frame sent by the display in
// response to a READ_OBJ (genie.ReadObject) request.
//

// Event Handler Function for Display 1
void myGenieEventHandler1(void)
{
  genieFrame Event;
  display1.DequeueEvent(&Event); // Remove the next queued event from the buffer, and process it below

  //If the cmd received is from a Reported Event (Events triggered from the Events tab of Workshop4 objects)
  if (Event.reportObject.cmd == GENIE_REPORT_EVENT)
  {
    if (Event.reportObject.object == GENIE_OBJ_SLIDER)                   // If the Reported Message was from a Slider
    {
      if (Event.reportObject.index == 0)                                 // If Slider0 (Index = 0)
      {
        int slider_val = display1.GetEventData(&Event);                  // Receive the event data from the Slider0
        display2.WriteObject(GENIE_OBJ_LED_DIGITS, 0, slider_val);       // Write Slider0 value of Display 1 to to LED Digits 0 of Display 2 !
      }
    }
  }

  //If the cmd received is from a Reported Object, which occurs if a Read Object (genie.ReadOject) is requested in the main code, reply processed here.
  if (Event.reportObject.cmd == GENIE_REPORT_OBJ)
  {
    if (Event.reportObject.object == GENIE_OBJ_USER_LED)                 // If the Reported Message was from a User LED
    {
      if (Event.reportObject.index == 0)                                 // If UserLed0 (Index = 0)
      {
        bool UserLed0_val = display1.GetEventData(&Event);               // Receive the event data from the UserLed0
        UserLed0_val = !UserLed0_val;                                    // Toggle the state of the User LED Variable
        display1.WriteObject(GENIE_OBJ_USER_LED, 0, UserLed0_val);       // Write UserLed0_val value back to to UserLed0
      }
    }
  }
}

// Event Handler Function for Display 2
void myGenieEventHandler2(void)
{
  genieFrame Event;
  display2.DequeueEvent(&Event); // Remove the next queued event from the buffer, and process it below

  //If the cmd received is from a Reported Event (Events triggered from the Events tab of Workshop4 objects)
  if (Event.reportObject.cmd == GENIE_REPORT_EVENT)
  {
    if (Event.reportObject.object == GENIE_OBJ_SLIDER)                   // If the Reported Message was from a Slider
    {
      if (Event.reportObject.index == 0)                                 // If Slider0 (Index = 0)
      {
        int slider_val = display2.GetEventData(&Event);                  // Receive the event data from the Slider0
        display1.WriteObject(GENIE_OBJ_LED_DIGITS, 0, slider_val);       // Write Slider0 value of Display 2 to to LED Digits 0 of Display 1
      }
    }
  }

  //If the cmd received is from a Reported Object, which occurs if a Read Object (genie.ReadOject) is requested in the main code, reply processed here.
  if (Event.reportObject.cmd == GENIE_REPORT_OBJ)
  {
    if (Event.reportObject.object == GENIE_OBJ_USER_LED)                 // If the Reported Message was from a User LED
    {
      if (Event.reportObject.index == 0)                                 // If UserLed0 (Index = 0)
      {
        bool UserLed0_val = display2.GetEventData(&Event);               // Receive the event data from the UserLed0
        UserLed0_val = !UserLed0_val;                                    // Toggle the state of the User LED Variable
        display2.WriteObject(GENIE_OBJ_USER_LED, 0, UserLed0_val);       // Write UserLed0_val value back to to UserLed0
      }
    }
  }

  /********** This can be expanded as more objects are added that need to be captured *************
  *************************************************************************************************
  Event.reportObject.cmd is used to determine the command of that event, such as an reported event
  Event.reportObject.object is used to determine the object type, such as a Slider
  Event.reportObject.index is used to determine the index of the object, such as Slider0
  genie.GetEventData(&Event) us used to save the data from the Event, into a variable.
  *************************************************************************************************/
}
