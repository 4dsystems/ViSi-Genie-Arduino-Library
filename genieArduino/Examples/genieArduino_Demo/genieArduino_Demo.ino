#include <genieArduino.h>

// Updated version of the genieArduino library and Demo
// 4D Systems
// This Demo communicates with a 4D Systems Display, configured with ViSi-Genie.
// The display has a slider, a cool gauge, an LED Digits and a string box.
// The program reads from the slider manually using Read Object as well as using the Reported Events
// from the On-Changed event from the slider itself, set in the Workshop4 software.
// Coolgauge is written to using Write Object, and the String is updated using the Write String command.

void setup() 
{ 
  // a few options to talk to the Display, uncomment the one you want
  genieBegin (GENIE_SERIAL, 115200);  //Serial0
  //genieBegin (GENIE_SERIAL_1, 9600);  //Serial1
  //genieBegin (GENIE_SERIAL_2, 9600);  //Serial2
  //genieBegin (GENIE_SERIAL_3, 9600);  //Serial3

  genieAttachEventHandler(myGenieEventHandler);

  //Reset the Display (change D4 to D2 if you have original 4D Arduino Adaptor)
  pinMode(4, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(4, 1);  // Reset the Display via D4
  delay(100);
  digitalWrite(4, 0);  // unReset the Display via D4
  
  delay (3500); //let the display start up

  //Turn the Display on (Contrast) - (Not needed but illustrates how)
  genieWriteContrast(1); // 1 = Display ON, 0 = Display OFF

  //Write a string to the Display
  genieWriteStr(0, GENIE_VERSION);
}

void loop() 
{ 
  static long waitPeriod = millis();
  static int gaugeAddVal = 1;
  static int gaugeVal = 50;

  genieDoEvents();

  if (millis() >= waitPeriod) 
  {
    // Write to CoolGauge0 with the value in the gaugeVal variable
    genieWriteObject(GENIE_OBJ_COOL_GAUGE, 0x00, gaugeVal); 
    gaugeVal += gaugeAddVal;
    if (gaugeVal == 99) gaugeAddVal = -1;
    if (gaugeVal == 0) gaugeAddVal = 1;

    // The results of this call will be available to myGenieEventHandler() after the display has responded
    // Do a manual read from the Slider0 object
    genieReadObject(GENIE_OBJ_SLIDER, 0x00);

    waitPeriod = millis() + 100;
  }
}


/////////////////////////////////////////////////////////////////////
//
// This is the user's event handler. It is called by genieDoEvents() 
// when the following conditions are true
//
//		The link is in an IDLE state, and
//		There is an event to handle
//
// The event can be either a REPORT_EVENT frame sent asynchrounously 
// from the display or a REPORT_OBJ frame sent by the display in
// response to a READ_OBJ request.
//

/*COMPACT VERSION HERE, LONGHAND VERSION BELOW WHICH MAY MAKE MORE SENSE
void myGenieEventHandler(void) 
{
  genieFrame Event;
  int slider_val = 0;   
  const int index = 0;  //HARD CODED TO READ FROM Index = 0, ie Slider0 as an example

  genieDequeueEvent(&Event);

  //Read from Slider0 for both a Reported Message from Display, and a Manual Read Object from loop code above
  if (genieEventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_SLIDER, index) ||
    genieEventIs(&Event, GENIE_REPORT_OBJ,   GENIE_OBJ_SLIDER, index)) 
  {
    slider_val = genieGetEventData(&Event);  // Receive the event data from the Slider0
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 0x00, slider_val);     // Write Slider0 value to to LED Digits 0
  }
}*/

//LONG HAND VERSION, MAYBE MORE VISIBLE AND MORE LIKE VERSION 1 OF THE LIBRARY
void myGenieEventHandler(void) 
{
  genieFrame Event;
  genieDequeueEvent(&Event);

  int slider_val = 0;

  //If the cmd received is from a Reported Event
  if(Event.reportObject.cmd == GENIE_REPORT_EVENT)
  {
    if (Event.reportObject.object == GENIE_OBJ_SLIDER)                // If the Reported Message was from a Slider
    {
      if (Event.reportObject.index == 0)                              // If Slider0
      {
        slider_val = (Event.reportObject.data_msb << 8) + Event.reportObject.data_lsb;  // Slider0 data into the slider_val setpoint  
        genieWriteObject(GENIE_OBJ_LED_DIGITS, 0x00, slider_val);     // Write Slider0 value to to LED Digits 0
      }
    }
  }

  //If the cmd received is from a Reported Object, which occurs if a Read Object is requested in the main code, reply processed here.
  if(Event.reportObject.cmd == GENIE_REPORT_OBJ)
  {
    if (Event.reportObject.object == GENIE_OBJ_SLIDER)                // If the Reported Message was from a Slider
    {
      if (Event.reportObject.index == 0)                              // If Slider0
      {
        slider_val = (Event.reportObject.data_msb << 8) + Event.reportObject.data_lsb;  // Slider0 data into the slider_val setpoint  
        genieWriteObject(GENIE_OBJ_LED_DIGITS, 0x00, slider_val);     // Write Slider0 value to to LED Digits 0
      }
    }
  }

  //This can be expanded as more objects are added that need to be captured

  //Event.reportObject.cmd is used to determine the command of that event, such as an reported event
  //Event.reportObject.object is used to determine the object type, such as a Slider
  //Event.reportObject.index is used to determine the index of the object, such as Slider0
  //Event.reportObject.data_msb and _lsb are used to save the data to a variable. They are in bytes, need to be combined to save as integer.
}

