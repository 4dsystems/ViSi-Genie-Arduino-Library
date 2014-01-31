/////////////////////// GenieArduino 31/01/2014 ///////////////////////
//
//      Library to utilize the 4D Systems Genie interface to displays
//      that have been created using the Visi-Genie creator platform.
//      This is intended to be used with the Arduino platform.
//
//		Improvements/Updates by
//		Clinton Keith, January 2014, www.clintonkeith.com		
//		4D Systems Engineering, January 2014, www.4dsystems.com.au
//		4D Systems Engineering, September 2013, www.4dsystems.com.au
//		Written by
//		Rob Gray (GRAYnomad), June 2013, www.robgray.com
//      Based on code by
//		Gordon Henderson, February 2013, <projects@drogon.net>
//
//      Copyright (c) 2012-2013 4D Systems Pty Ltd, Sydney, Australia
/*********************************************************************
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
 *********************************************************************/
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#include <stdint.h>

#ifndef genieArduino_h
#define genieArduino_h

#undef	GENIE_DEBUG

#define	GENIE_VERSION	"GenieArduino 31-Jan-2014"

// Genie commands & replys:

#define	GENIE_ACK		0x06
#define	GENIE_NAK		0x15

#define TIMEOUT_PERIOD	1000
#define RESYNC_PERIOD	100

#define	GENIE_READ_OBJ			0
#define	GENIE_WRITE_OBJ			1
#define	GENIE_WRITE_STR			2
#define	GENIE_WRITE_STRU		3
#define	GENIE_WRITE_CONTRAST	4
#define	GENIE_REPORT_OBJ		5
#define	GENIE_REPORT_EVENT		7

// Objects
//	the manual says:
//		Note: Object IDs may change with future releases; it is not
//		advisable to code their values as constants.

#define	GENIE_OBJ_DIPSW			0
#define	GENIE_OBJ_KNOB			1
#define	GENIE_OBJ_ROCKERSW		2
#define	GENIE_OBJ_ROTARYSW		3
#define	GENIE_OBJ_SLIDER		4
#define	GENIE_OBJ_TRACKBAR		5
#define	GENIE_OBJ_WINBUTTON		6
#define	GENIE_OBJ_ANGULAR_METER	7
#define	GENIE_OBJ_COOL_GAUGE	8
#define	GENIE_OBJ_CUSTOM_DIGITS	9
#define	GENIE_OBJ_FORM			10
#define	GENIE_OBJ_GAUGE			11
#define	GENIE_OBJ_IMAGE			12
#define	GENIE_OBJ_KEYBOARD		13
#define	GENIE_OBJ_LED			14
#define	GENIE_OBJ_LED_DIGITS	15
#define	GENIE_OBJ_METER			16
#define	GENIE_OBJ_STRINGS		17
#define	GENIE_OBJ_THERMOMETER	18
#define	GENIE_OBJ_USER_LED		19
#define	GENIE_OBJ_VIDEO			20
#define	GENIE_OBJ_STATIC_TEXT	21
#define	GENIE_OBJ_SOUND			22
#define	GENIE_OBJ_TIMER			23
#define	GENIE_OBJ_SPECTRUM		24
#define	GENIE_OBJ_SCOPE			25
#define	GENIE_OBJ_TANK			26
#define	GENIE_OBJ_USERIMAGES	27
#define	GENIE_OBJ_PINOUTPUT		28
#define	GENIE_OBJ_PININPUT		29
#define	GENIE_OBJ_4DBUTTON		30
#define	GENIE_OBJ_ANIBUTTON		31
#define	GENIE_OBJ_COLORPICKER	32
#define	GENIE_OBJ_USERBUTTON	33

// Structure to store replys returned from a display

#define		GENIE_FRAME_SIZE	6

struct genieFrameReportObj {
	uint8_t		cmd;
	uint8_t		object;
	uint8_t		index;
	uint8_t		data_msb;
	uint8_t		data_lsb;
};

/////////////////////////////////////////////////////////////////////
// The Genie frame definition
//
// The union allows the data to be referenced as an array of uint8_t
// or a structure of type genieFrameReportObj, eg
//
//	genieFrame f;
//	f.bytes[4];
//	f.reportObject.data_lsb
//
//	both methods get the same byte
//
union genieFrame {
	uint8_t				bytes[GENIE_FRAME_SIZE];
	genieFrameReportObj	reportObject;
};

#define	MAX_GENIE_EVENTS	16	// MUST be a power of 2
#define	MAX_GENIE_FATALS	10

struct genieEventQueueStruct {
	genieFrame	frames[MAX_GENIE_EVENTS];
	uint8_t		rd_index;
	uint8_t		wr_index;
	uint8_t		n_events;
};

typedef enum {
    GENIE_NULL,
    GENIE_SERIAL,
    GENIE_SERIAL_1,
    GENIE_SERIAL_2,
    GENIE_SERIAL_3
} genie_port_types;


//typedef void		(*geniePutCharFuncPtr)		(uint8_t c, uint32_t baud);
//typedef uint16_t	(*genieGetCharFuncPtr)		(void);
typedef void		(*genieUserEventHandlerPtr) (void);

/////////////////////////////////////////////////////////////////////
// User API functions
// These function prototypes are the user API to the library
//
extern void			genieSetup				(uint32_t baud);
extern void     	genieBegin				(Stream &serial);
extern uint16_t 	genieBegin				(uint8_t port, uint32_t baud);
extern bool			genieReadObject			(uint16_t object, uint16_t index);
extern uint16_t		genieWriteObject		(uint16_t object, uint16_t index, uint16_t data);
extern void			genieWriteContrast		(uint16_t value);
extern uint16_t		genieWriteStr			(uint16_t index, char *string);
extern uint16_t		genieWriteStrU			(uint16_t index, uint16_t *string);
extern bool			genieEventIs			(genieFrame * e, uint8_t cmd, uint8_t object, uint8_t index);
extern uint16_t 	genieGetEventData		(genieFrame * e);
extern uint16_t		genieDoEvents			(void);
extern void			genieAttachEventHandler (genieUserEventHandlerPtr userHandler);
extern bool			genieDequeueEvent		(genieFrame * buff);

extern void			pulse 					(int pin);
extern void     	assignDebugPort			(Stream &port);

#ifndef	TRUE
#define	TRUE	(1==1)
#define	FALSE	(!TRUE)
#endif

#define	ERROR_NONE			0
#define	ERROR_TIMEOUT		-1	// 255  0xFF
#define	ERROR_NOHANDLER		-2	// 254  0xFE
#define	ERROR_NOCHAR		-3	// 253  0xFD
#define	ERROR_NAK			-4	// 252  0xFC
#define	ERROR_REPLY_OVR		-5	// 251  0xFB
#define	ERROR_RESYNC		-6	// 250  0xFA
#define	ERROR_NODISPLAY		-7	// 249  0xF9
#define ERROR_BAD_CS		-8	// 248  0xF8

#define GENIE_LINK_IDLE			0
#define GENIE_LINK_WFAN			1 // waiting for Ack or Nak
#define GENIE_LINK_WF_RXREPORT	2 // waiting for a report frame
#define GENIE_LINK_RXREPORT		3 // receiving a report frame
#define GENIE_LINK_RXEVENT		4 // receiving an event frame
#define GENIE_LINK_SHDN			5

#define GENIE_EVENT_NONE	0
#define GENIE_EVENT_RXCHAR	1

#endif