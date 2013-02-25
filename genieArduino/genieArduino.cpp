/*
 * genieArduino.c:
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

#if (ARDUINO >= 100)
# include "Arduino.h" // for Arduino 1.0
#else
# include "WProgram.h" // for Arduino 23
#endif

//#include <avr/interrupt.h>
//#include <avr/io.h>

#include "genieArduino.h"

#ifndef	TRUE
#define	TRUE	(1==1)
#define	FALSE	(!TRUE)
#endif

// Input buffer:
//      max. unprocessed replys from the display

#define MAX_GENIE_REPLYS        16

static struct genieReplyStruct genieReplys [MAX_GENIE_REPLYS] ;
static int genieReplysHead = 0 ;
static int genieReplysTail = 0 ;

static int genieAck = FALSE ;
static int genieNak = FALSE ;


/*
 * baudRate:
 *	Calculate the baud rate numbers for the AVR (Arduino) serial ports,
 *	taking into account the error factor to use x2 mode or not.
 *********************************************************************************	
 */

static void baudRate (uint32_t baud, uint8_t *lo, uint8_t *hi, int8_t *u2x)
{
  uint8_t  nonu2x_baud_error ;
  uint8_t  u2x_baud_error ;
  uint16_t setting ;

// U2X mode is needed for baud rates higher than (CPU Hz / 16)

  if (baud > F_CPU / 16)
    *u2x = TRUE ;
  else
  {

// Calculate the percent difference between the baud-rate specified and the
//	real baud rate for both U2X and non-U2X mode (0-255 error percent)

    nonu2x_baud_error = abs ((int)(255 - ((F_CPU / (16 * (((F_CPU / 8 / baud - 1) / 2) + 1)) * 255) / baud))) ;
    u2x_baud_error    = abs ((int)(255 - ((F_CPU / ( 8 * (((F_CPU / 4 / baud - 1) / 2) + 1)) * 255) / baud))) ;

// Figure out of U2X mode would allow for a better connection, so
//	we prefer non-U2X mode because it handles clock skew better

    *u2x = (nonu2x_baud_error > u2x_baud_error) ;
  }

  if (*u2x)
    setting = (F_CPU / 4 / baud - 1) / 2 ;
  else
    setting = (F_CPU / 8 / baud - 1) / 2 ;

  *hi = setting >> 8 ;
  *lo = setting & 0xFF ;
}


/*
 * USART_RX_vect:
 *	Character RX interrupt vector
 *	This is the heart of the system - we use it to read in data from
 *	the display and save it for later reading.
 *********************************************************************************
 */

#if !defined (USART0_RX_vect)
#	define USART0_RX_vect USART_RX_vect
#endif

ISR(USART0_RX_vect)
{
  uint8_t data ;
  static uint8_t cmd, object, index, msb, lsb ;
  static uint8_t checksum ;
  static uint8_t state = 0 ;
  struct genieReplyStruct *reply ;
  int next ;

  data = UDR0 ;

  switch (state)
  {
    case 0:
      /**/ if (data == GENIE_ACK)
	genieAck = TRUE ;
      else if (data == GENIE_NAK)
	genieNak = TRUE ;
      else
      {
	checksum = data ;
	cmd      = data ;
	state = 1 ;
      }
      return ;

    case 1:
      checksum ^= data ;
      object    = data ;
      state     = 2 ;
      return ;

    case 2:
      checksum ^= data ;
      index     = data ;
      state     = 3 ;
      return ;

    case 3:
      checksum ^= data ;
      msb       = data ;
      state     = 4 ;
      return ;

    case 4:
      checksum ^= data ;
      lsb       = data ;
      state     = 5 ;
      return ;

    case 5:
      state = 0 ;

      if (data == checksum)
	break ;

      return ;
    }

// We have valid data - store it into the buffer

  next = (genieReplysHead + 1) & (MAX_GENIE_REPLYS - 1) ;
  if (next != genieReplysTail)                        // Discard rather than overflow
  {
    reply = &genieReplys [genieReplysHead] ;
    reply->cmd    = cmd ;
    reply->object = object ;
    reply->index  = index ;
    reply->data   = msb << 8 | lsb ;
    genieReplysHead = next ;
  }
}



/*
 * geniePutchar:
 *	Output the supplied character over the serial port to the Genie display
 *********************************************************************************
 */

static void geniePutchar (uint8_t c)
{
  while ((UCSR0A & _BV (UDRE0)) == 0)
    ;

  UDR0 = c ;
}


/*
 * genieReplyAvail:
 *      Return TRUE if there are pending messages from the display
 *********************************************************************************
 */

int genieReplyAvail (void)
{
  return (genieReplysHead != genieReplysTail) ;
}

/*
 * genieGetReply:
 *      Get the next message out of the Genie Reply queue, or
 *      wait until a message has been sent from the display
 *********************************************************************************
 */

void genieGetReply (struct genieReplyStruct *reply)
{
  while (!genieReplyAvail ())
    delay (1) ;

  memcpy (reply, &genieReplys [genieReplysTail], sizeof (struct genieReplyStruct)) ;

  genieReplysTail = (genieReplysTail + 1) & (MAX_GENIE_REPLYS - 1) ;
}


/*
 * genieReadObj:
 *      Send a read object command to the Genie display and get the result back
 *********************************************************************************
 */

int genieReadObj (int object, int index)
{
  struct genieReplyStruct reply ;
  uint32_t timeUp ;
  uint8_t checksum ;

// Discard any pending replys

  while (genieReplyAvail ())
    genieGetReply (&reply) ;

  genieAck = genieNak = FALSE ;

  geniePutchar (GENIE_READ_OBJ) ; checksum   = GENIE_READ_OBJ ;
  geniePutchar (object) ;         checksum  ^= object ;
  geniePutchar (index) ;          checksum  ^= index ;
  geniePutchar (checksum) ;

// Wait up to 50mS for a reply
//      Note: @9600 baud 5 characters will take 5mS!

  for (timeUp = millis () + 50 ; millis () < timeUp ;)
  {
    if (genieNak)
      return -1 ;

    if (genieReplyAvail ())
    {
      genieGetReply (&reply) ;
      if ((reply.cmd == GENIE_REPORT_OBJ) && (reply.object == object) && (reply.index == index))
        return reply.data ;
    }

    delayMicroseconds (101) ;
  }

  return -1 ;
}


/*
 * genieWriteObj:
 *      Write data to an object on the display
 *********************************************************************************
 */

int genieWriteObj (int object, int index, unsigned int data)
{
  unsigned int msb, lsb ;
  uint8_t checksum ;

  lsb = (data >> 0) & 0xFF ;
  msb = (data >> 8) & 0xFF ;

  genieAck = genieNak = FALSE ;

  geniePutchar (GENIE_WRITE_OBJ) ; checksum  = GENIE_WRITE_OBJ ;
  geniePutchar (object) ;          checksum ^= object ;
  geniePutchar (index) ;           checksum ^= index ;
  geniePutchar (msb) ;             checksum ^= msb ;
  geniePutchar (lsb) ;             checksum ^= lsb ;
  geniePutchar (checksum) ;

// TODO: Really ought to timeout here, but if the display doesn't
//      respond, then it's probably game over anyway.

  while ((genieAck == FALSE) && (genieNak == FALSE))
    delay (1) ;

  return 0 ;
}


/*
 * genieWriteContrast:
 *      Alter the display contrast (backlight)
 *********************************************************************************
 */

int genieWriteContrast (int value)
{
  unsigned int checksum ;

  genieAck = genieNak = FALSE ;

  geniePutchar (GENIE_WRITE_CONTRAST) ; checksum  = GENIE_WRITE_CONTRAST ;
  geniePutchar (value) ;                checksum ^= value ;
  geniePutchar (checksum) ;

// TODO: Really ought to timeout here, but if the display doesn't
//      respond, then it's probably game over anyway.

  while ((genieAck == FALSE) && (genieNak == FALSE))
    delay (1) ;

  return 0 ;
}


/*
 * genieWriteStr:
 * genieWriteStrU:
 *      Write a string to the display (ASCII, or Unicode)
 *      There is only one string type object.
 *********************************************************************************
 */

static int _genieWriteStrX (int code, int index, char *string)
{
  char *p ;
  unsigned int checksum ;
  int len = strlen (string) ;

  if (len > 255)
    return -1 ;

  genieAck = genieNak = FALSE ;

  geniePutchar (code) ;               checksum  = code ;
  geniePutchar (index) ;              checksum ^= index ;
  geniePutchar ((unsigned char)len) ; checksum ^= len ;
  for (p = string ; *p ; ++p)
  {
    geniePutchar (*p) ;
    checksum ^= *p ;
  }
  geniePutchar (checksum) ;

// TODO: Really ought to timeout here, but if the display doesn't
//      respond, then it's probably game over anyway.

  while ((genieAck == FALSE) && (genieNak == FALSE))
    delay (1) ;

  return 0 ;
}

int genieWriteStr (int index, char *string)
{
  int result ;

  result = _genieWriteStrX (GENIE_WRITE_STR, index, string) ;

  return result ;
}

int genieWriteStrU (int index, char *string)
{
  int result ;

  result = _genieWriteStrX (GENIE_WRITE_STRU, index, string) ;

  return result ;
}


/*
 * genieSetup:
 *	Initialise the standard serial port in the AVR Mega chips, and setup
 *	the communications with the Genie display
 *********************************************************************************
 */

void genieSetup (uint32_t baud)
{
  uint8_t hi, lo ;
  int8_t    u2x ;

  baudRate (baud, &lo, &hi, &u2x) ;

  if (u2x)
    UCSR0A  |= (1 << U2X0) ;
  else
    UCSR0A  &= ~(1 << U2X0) ;

  UBRR0H = hi ;
  UBRR0L = lo ;

  (void)UDR0 ;	// dummy read to clear any flag

// Set Rx enable, Tx enable flags and
//	Rx Complete Interrupt flag

  UCSR0B = _BV (RXEN0) | _BV (TXEN0) | _BV (RXCIE0)  ;
}
