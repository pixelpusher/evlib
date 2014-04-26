/**
 * @file Oneshot.h
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
 * A one-shot event class for triggering something to happen once, over a period of time
 * 
 */

#ifndef __COSA_ONESHOT_HH__
#define __COSA_ONESHOT_HH__

#include "Cosa/Types.h"
#include "Cosa/Linkage.hh"
#include "Cosa/Watchdog.hh"

/**
 * Oneshot function handler. Syntactic sugar for watchdog timeout
 * event handlers. Subclass and implement the virtual method run()
 * as the function to be executed periodically.
 *
 * @section Limitations
 * Avoid setting period to the same value in the run method as this
 * will force the function to be executed twice in the same time frame. 
 * Also, might want to modify to use millis() for better timing precision.
 *
 * @section See Also
 * In Cosa: Activity.hh. For details on time period handling see Watchdog.hh. 
 * This execution pattern is also available in the FSM (Finite State Machine) class.
 */
class Oneshot : protected Link {
public:

  /**
   * Construct a oneshot function handler that updates continually until finished.
   *
   * @param[in] ms period of timeout.
   */
  Oneshot(uint16_t ms = 16) : 
    Link(), 
    m_duration(ms),
    running(false)
  {
  	  refreshInterval = 16;
	  reset();
  }

  /**
   * Set timeout period.
   * @param[in] ms period of timeout.
   */
  Oneshot& duration(uint16_t ms)
  {
    m_duration = ms;
    return *this;
  }

  /**
   * Get timeout period.
   */
  uint16_t get_duration()
  {
    return m_duration;
  }

  void reset()
  {
	percentFinished = 0;
    m_elapsedTime = 0;
  }

  /**
   * Start the periodic function.
   */
  void start(uint16_t ms)
  {
  	// how about a check for minimum values, e.g. if it's 0?
  	m_duration = ms;
  	reset();
  	running = true;
    Watchdog::attach(this, refreshInterval);
  }

  /**
   * Stop the periodic function.
   */
  void stop()
  {
    detach();
    running = false;
  }

  /**
   * Is this currently running or stopped?
   */
  bool isRunning()
  {
	return running;
  }

  /**
   * @override Periodic
   * The default null function. 
   */
  virtual void run() {}

private:
  /**
   * @override Event::Handler
   * Periodic event handler; dispatch the run() function on
   * timeout events.
   * @param[in] type the type of event.
   * @param[in] value the event value.
   */
  virtual void on_event(uint8_t type, uint16_t value)
  {
    if (type != Event::TIMEOUT_TYPE) return;
    
	// update elapsed time
    m_elapsedTime += refreshInterval;

    // check if we've gone outside of our elapsed time. if so, stop.
    if ( m_elapsedTime >= m_duration)
    {
		percentFinished = 1;
		stop();
	}
	else
	{    	
	    percentFinished = ((float)m_elapsedTime) / m_duration;
    	run();
    }
  }

  ///// class variables //////////////
  private:
  
  uint16_t m_duration;	// total time to run for
  uint16_t m_elapsedTime;

  protected:
  
  float percentFinished;
  volatile bool running; // because of run
  uint16_t refreshInterval;	// time between updates - the run() function
};

#endif
