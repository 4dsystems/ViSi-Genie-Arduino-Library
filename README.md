![image](http://www.4dsystems.com.au/imagenes/header.png)

ViSi-Genie-Arduino-Library - NEW VERSION - Updated 09-Jan-2014
==============================================================

Arduino Library for 4D Systems ViSi-Genie Environment 

## Information

This library provides high level functions for the Arduino, to ease communication with 4D Systems modules when using the module configured with ViSi-Genie.
Please refer to the 4D Systems website, namingly the Workshop 4 Product Page, for documentation regarding Workshop 4, and its environments.

## Installation

Library folder should be placed in the C:\Users\(User name)\My Documents\Arduino\Libraries\ folder, or equivalent. (restart the IDE if already open).

PLEASE ensure that the old library (if installed) has been removed completely so it does not conflict.

For more information on the installation, please refer to [Installing Additional Arduino Libraries] (http://arduino.cc/en/Guide/Libraries)

Open the ViSi-Genie project using Workshop4 and download to your display, connect the display to Arduino, reset the Arduino and it should work.

## Example Sketch

Inside the library is an example sketch, to assist with getting started using this library. Inside is also a ViSi-Genie Workshop4 project, which can be used on a range of 4D Systems displays (designed on a uLCD-32PTU however can be changed via Workshop4 menu). It illustrates how to use some of the commands in the library include Read Object, Write Object, Reported Messages, Write Contrast and Write String.

## Tested with

This library has been tested on the Duemilanove, Uno, Mega 1280, Mega 2560, Due and new Intel Galileo. Any problems discovered with this library, please contact technical support so fixes can be put in place, or seek support from our forum.