/**
 * @file CosaBlinkPeriodic.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2012-2014, Mikael Patel, modified by Evan Raskob http://pixelist.info
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
 * The classic LED blink example using a periodic function handler.
 *
 * @section Circuit
 * Connect an RGB LED to pins (D5,D6,D7/Arduino, D1,D2,D3/Tiny).
 *
 */

#include <Blinker.h>


// blink an LED at 200ms
Blinker led1(Board::D5, 200);

// blink an LED at 300ms, start with it on (state is 1)
Blinker led2(Board::D6, 300, 1);


void setup()
{
  // DON'T TOUCH THIS CODE ///////////////////////////
  // This starts the event timing system.
  // Start the watchdog ticks and push time events
  Watchdog::begin(16, Watchdog::push_timeout_events);
  ////////////////////////////////////////////////////
  

  // Start the LEDs blinking
  led1.begin();
  led2.begin();
  
  // to stop them later, for example, use: led1.end();
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
