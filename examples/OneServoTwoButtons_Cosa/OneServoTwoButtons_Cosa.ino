/**
 * @file OneServoTwoButtons_Cosa.ino
 * @version 0.1
 *
 * @section License
 * Copyright (C) 2014, Evan Raskob - http://pixelist.info
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
 * Demonstration of using multiple buttons and oneshot events (controlling servos).
 *
 * @section Circuit
 * Connect a servo to digital pin 9 on the Arduino (and possibly another to pin 8)
 * as shown, and two buttons (and 10k resistors), one on pin 9 and the other on pin 8.
 *
 *                       Servo#0/servo
 *                       +------------+
 * (D9)----------------1-|PULSE   I   |
 * (VCC)---------------2-|VCC   ==o== |
 * (GND)---------------3-|GND     I   |
 *                       +------------+
 *
 */


#include <OneshotButton.h>
#include <ServoController.h>


// this takes care of the timing of the servo buttons and rotations
OneShotServoController::Scheduler servoScheduler;


// we can use up to 2 servos with this class 
Servo servo(0, Board::D9); // set up a Servo (number 0) on pin digital 9
//Servo servo2(1, Board::D8); // set up a Servo (number 1) on pin digital 8

// these two objects will control the servo's rotation over time, at
// different speeds and over different durations. They will be started/stopped by
// the OneshotButtons below.

OneShotServoController servoControl1(servo);
OneShotServoController servoControl2(servo);

// create a button to trigger servoControl1 - see below
OneshotButton servoButton1(Board::D2, (ControlAction&) servoControl1);

// create a button to trigger servoControl2 - see below
OneshotButton servoButton2(Board::D3, (ControlAction&) servoControl2);


//
// this runs once when the program starts
//
void setup()
{
  // DON'T TOUCH THIS CODE ///////////////////////////
  
  // This starts the event timing system.
  // Start the watchdog ticks and push time events
  Watchdog::begin(8, Watchdog::push_timeout_events);

  RTC::begin(); // Real Time Clock for fine timing of events

  Servo::begin();  // start servo port handling for all servos

  servoScheduler.begin();  // start servo events (button and rotation) handling
  
  ////////////////////////////////////////////////////


  // EDIT HERE  //////////////////////////////////////  
  // start buttons listening (you can stop them too, using button.end()
  servoButton1.begin();
  servoButton2.begin();
  
  // set the initial angle to 20 degrees
  servo.set_angle(20);
  
  delay(2000); // wait 2 seconds for no good reason
 
  // set both the start and end angles, and duration of the rotation
  servoControl1.startAngle(10)
  	        .endAngle(179)
  	        .duration(2000);

  servoControl2.startAngle(100)
                .endAngle(30)
                .duration(200); // fast!
  ////////////////////////////////////////////////////
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
