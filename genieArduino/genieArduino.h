/*
 * genieArduino.h:
 *      Library to utilise the 4D Systems Genie interface to displays
 *      that have been created using the Visi-Genie creator platform.
 *      This is intended to be used with the Arduino platform.
 *
 *      Gordon Henderson, February 2013, <projects@drogon.net>
 *      Copyright (c) 2012-2013 4D Systems PTY Ltd, Sydney, Australia
 ***********************************************************************
 * This file is part of genieArduino:
 *    genieArduino is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as
 *    published by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    genieArduino is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with genieArduino.
 *    If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#ifndef genieArduino_h
#define genieArduino_h

//#include "Arduino.h"

#include <stdint.h>

#undef	GENIE_DEBUG

// Genie commands & replys:

#define	GENIE_ACK		0x06
#define	GENIE_NAK		0x15

#define	GENIE_READ_OBJ		0
#define	GENIE_WRITE_OBJ		1
#define	GENIE_WRITE_STR		2
#define	GENIE_WRITE_STRU	3
#define	GENIE_WRITE_CONTRAST	4
#define	GENIE_REPORT_OBJ	5
#define	GENIE_REPORT_EVENT	7

// Objects
//	the manual says:
//		Note: Object IDs may change with future releases; it is not
//		advisable to code their values as constants.

#define	GENIE_OBJ_DIPSW		 0
#define	GENIE_OBJ_KNOB		 1
#define	GENIE_OBJ_ROCKERSW	 2
#define	GENIE_OBJ_ROTARYSW	 3
#define	GENIE_OBJ_SLIDER	 4
#define	GENIE_OBJ_TRACKBAR	 5
#define	GENIE_OBJ_WINBUTTON	 6
#define	GENIE_OBJ_ANGULAR_METER	 7
#define	GENIE_OBJ_COOL_GAUGE	 8
#define	GENIE_OBJ_CUSTOM_DIGITS	 9
#define	GENIE_OBJ_FORM		10
#define	GENIE_OBJ_GAUGE		11
#define	GENIE_OBJ_IMAGE		12
#define	GENIE_OBJ_KEYBOARD	13
#define	GENIE_OBJ_LED		14
#define	GENIE_OBJ_LED_DIGITS	15
#define	GENIE_OBJ_METER		16
#define	GENIE_OBJ_STRINGS	17
#define	GENIE_OBJ_THERMOMETER	18
#define	GENIE_OBJ_USER_LED	19
#define	GENIE_OBJ_VIDEO		20
#define	GENIE_OBJ_STATIC_TEXT	21
#define	GENIE_OBJ_SOUND		22
#define	GENIE_OBJ_TIMER		23

// Structure to store replys returned from a display

struct genieReplyStruct
{
  int cmd ;
  int object ;
  int index ;
  unsigned int data ;
} ;

// Globals (for debugging, mostly)

#ifdef	GENIE_DEBUG
    int genieChecksumErrors  ;
    int genieTimeouts ;
    int genieAck ;
    int genieNak ;
#endif

// Functions

extern int  genieReplyAvail    (void) ;
extern void genieGetReply      (struct genieReplyStruct *reply) ;

extern int  genieReadObj       (int object, int index) ;
extern int  genieWriteObj      (int object, int index, unsigned int data) ;
extern int  genieWriteContrast (int value) ;
extern int  genieWriteStr      (int index, char *string) ;
extern int  genieWriteStrU     (int index, char *string) ;

extern void genieSetup         (uint32_t baud) ;

#endif
