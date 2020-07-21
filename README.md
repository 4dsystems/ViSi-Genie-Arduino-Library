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

Inside the library are 3 example sketches, to assist with getting started using this library. Inside is also a ViSi-Genie Workshop4 project, which can be used on a range of 4D Systems displays (designed on a uLCD-32PTU however can be changed via Workshop4 menu). It illustrates how to use some of the commands in the library include Read Object, Write Object, Reported Messages, Write Contrast and Write String.

## Tested with

This library has been tested on the Duemilanove, Uno, Mega 1280, Mega 2560, Leonardo, Chipkit Max32, Due, Intel Galileo, Teensy and Yun (Software Serial only on Yun). 
Any problems discovered with this library, please contact technical support so fixes can be put in place, or seek support from our forum.

## Compatible 4D Systems Display Modules

This library will work with all 4D Systems Modules which are capable of using the ViSi-Genie environment. This is therefore all Picaso, Pixxi-28, Pixxi-44 and Diablo16 Display Modules.
The demo included with this library was made for the gen4-uLCD-32DCT-CLB (3.2" Capacitive Touch gen4 module) however can easily be adapted to other size displays.

## Questions/Issues?

Please sign up for our Forum and ask a question there, or submit a Tech Support Ticket from our website.
http://forum.4dsystems.com.au or http://www.4dsystems.com.au/support
Feel free to add a Github issue if you find a problem, we will do our best to help solve the problem.
