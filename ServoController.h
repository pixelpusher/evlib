/**
 *
 * @file OneShotServoController.h
 * @version 0.1
 *
 * @section License
 * Copyright (C) 2014, Evan Raskob - http://pixelist.info and Mikael Patel 2013-14
 * Based in part on Alarm.hh and Alarm.cpp from the Arduino Che Cosa project
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
 * Provides methods for rotating a servo over a period of time.  Can be used concurrently
 * with other OneShotServoControllers, and, when started, the latest will take control of 
 * the servo and detach the other controller(s) neatly.
 *
 * @section TODO
 * Add some protection to start and stop angle functions. Exception handling?
 */
 
#ifndef __SERVOONESHOT_HH__
#define __SERVOONESHOT_HH__

#include "Cosa/RTC.hh"
#include "Cosa/Servo.hh"
#include "Cosa/Periodic.hh"

#include <ControlAction.h> // evlib


class OneShotServoController : public ControlAction {

public:

  OneShotServoController(Servo& servo) :  
    m_duration(1000), 
    m_servo(&servo)
    { }

    OneShotServoController& duration(uint32_t _duration)
    {
	m_duration = _duration;	// set the duration of this movement
  	
	return *this;
    }

/*  
 * start the servo moving from start to finish over a time in ms
 */
  
  virtual void start();
  
  /**
   * Remove the controller handler from the list. 
   */
  virtual void stop()
  {
    detach();
  }
  
  
  /*
   * sets m_finished true if needs to be deactivated
   */ 
  virtual void run();
  
  
  /**
   * Set the reference to the servo to control
   */
  OneShotServoController& startAngle(int _startAngle)
  {
  	m_startAngle = _startAngle;
  	return *this;
  }

  /**
   * Set the reference to the servo to control
   */
  OneShotServoController& endAngle(int _endAngle)
  {
  	m_endAngle = _endAngle;
  	return *this;
  }

  /**
   * Set the reference to the servo to control
   */

  OneShotServoController& servo(Servo& _servo)
  {
  	m_servo = (&_servo);
  }
  
/*
 * Update all servo callbacks
 *
 */
static void update(uint32_t ms);

/**
   * Watchdog based periodic(8 ms) scheduler. The setup function
   * must initiate the Watchdog to generate timeout event, 
   *   Watchdog::begin(ms, mode, Watchdog::push_timeout_events)
   * and the loop function must contain an event dispatcher,
   *   Event event;
   *   Event::queue.await(&event);
   *   event.dispatch();
   * The alarm manager will check for expired alarms and call the
   * respective alarm handlers. The RTC is used for more accurate
   * timekeeping.
   */
  class Scheduler : public Periodic {
  public:
    Scheduler() : 
      Periodic(32)
    {
    }
    
    virtual void run();

    static uint32_t s_ms;
	
  //private:
  };

private:

  Servo* m_servo;
  int m_startAngle;
  int m_endAngle;
  int m_currentAngle;
  
  uint32_t m_startTime;
  uint32_t m_elapsedTime;
  uint32_t m_duration;
  float percentFinished;
  bool m_finished;

  // servo callbacks handler queue
  static Head s_callbacksQueue;
};

#endif
