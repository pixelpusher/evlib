/**
 * @file OneShotServo_Cosa.ino
 * @version 0.1
 *
  * @section License
 * Copyright (C) 2014, Mikael Patel, Evan Raskob - http://pixelist.info
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
 * Demonstration of the Servo control class and Oneshot events.
 *
 * @section Circuit
 *                       Servo#0/servo
 *                       +------------+
 * (D9)----------------1-|PULSE   I   |
 * (VCC)---------------2-|VCC   ==o== |
 * (GND)---------------3-|GND     I   |
 *                       +------------+
 *
 */

#include "Cosa/Servo.hh"
#include "Cosa/Watchdog.hh"
#include "Cosa/Event.hh"

#include <ServoController.h>


// we can use up to 2 servos with this class
// 
Servo servo(0, Board::D9); // set up a Servo (number 0) on pin digital 9


OneShotServoController servoControl(servo);

void setup()
{
  // DON'T TOUCH THIS CODE ///////////////////////////
  // This starts the event timing system.
  // Start the watchdog ticks and push time events
  Watchdog::begin(8, Watchdog::push_timeout_events);
  ////////////////////////////////////////////////////


  // Start servo handling for all
  Servo::begin();
  
  // set the initial angle to 10 degrees
  servo.set_angle(10);
  
  // set both the start and end angle
  servoControl.startAngle(10)
  		.endAngle(179)
  		.duration(4000);
  
  // start the servo moving from start to end angle in 4000ms (4 sec)
  servoControl.start();	
  
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
