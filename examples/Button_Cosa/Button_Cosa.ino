/**
 * @file Button_Cosa.ino
 * @version 0.1
 *
 * @section License
 * Copyright (C) 2014, Mikael Patel & Evan Raskob - http://pixelist.info 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 *
 * This file is part of the evlib Arduino library and uses the Arduino Che Cosa project
 * by the talented Mikael Patel (and others)
 *
 * @section Description
 * Demonstrated an on/off button using Cosa and evlib.  Attach a standard buttons
 * to digital pin 2 and also to digital pin 3, and when either is pressed (or closed)
 * then pin 13 (built-in LED) will light up.
 *
 * @section Circuit
 * Connect buttons to each of the pins D2 & D3 on an Arduino
 */


#include <OnOffButton.h>  // include the other file in this sketch

#include "Cosa/Event.hh"
#include "Cosa/Watchdog.hh"


// standard button - good for touch inputs (64ms)
// attached to digital pin 2, will toggle digital 13 (built-in LED) on or off

OnOffButton button (Board::D2, Board::D13);

// faster button - good for detecting quick inputs (16ms)
// attached to digital pin 3, will toggle digital 13 (built-in LED) on or off

FastOnOffButton fastButton (Board::D3, Board::D13);


void setup()
{
  // DON'T TOUCH THIS CODE ///////////////////////////
  // This starts the event timing system.
  // Start the watchdog ticks and push time events
  Watchdog::begin(16, Watchdog::push_timeout_events);
  ////////////////////////////////////////////////////


  // EDIT HERE  /////////////
  // Start the button handler
  
  button.begin();
  fastButton.begin();
  
}

void loop()
{
  // DON'T TOUCH THIS CODE ///////////////////////////
  // This runs the event timing system.
  // Wait for events (low power mode) and dispatch
  Event event;
  Event::queue.await(&event);
  event.dispatch();
  ////////////////////////////////////////////////////
  
  
  // do other stuff...
}
