/**
 *
 * @file OneShotServoController.h
 * @version 0.1
 *
 * @section License
 * Copyright (C) 2014, Evan Raskob <e.raskob@rave.ac.uk>, http://pixelist.info
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
 * @section Description
 * Demonstration of the Servo control class.
 *
 * @section TODO
 * Add some protection to start and stop angle functions. Exception handling?
 */
 

#include <ServoController.h>


// for debugging
#if DEBUG
#include "Cosa/Trace.hh"
#include "Cosa/IOStream/Driver/UART.hh"
#endif

uint32_t OneShotServoController::Scheduler::s_ms;
// servo callbacks handler queue
Head OneShotServoController::s_callbacksQueue;

/*  
 * start the servo moving from start to finish over a time in ms
 */  
  void OneShotServoController::start()
  {
  	m_finished = false;	// we are just started!
  	
  	m_startTime = RTC::millis();	// update start time to current time

    #if DEBUG
    trace << PSTR("start: ") << m_startTime << ':'
	<< RTC::millis()
	<< endl;
    #endif
    
  	// go through list of attached callbacks
  	// if one is already enabled with the same servo, then disable it
  	// if we are already on the list, don't add ourselves twice!
  	
  	OneShotServoController* scontrol = (OneShotServoController*) s_callbacksQueue.get_succ(); 
	while (scontrol != (OneShotServoController*) &s_callbacksQueue) { // while not the 1st one

            #if DEBUG
	    trace << scontrol << ':' << this << endl;
            #endif
          
            OneShotServoController* current = scontrol;
            // make sure not to detach the one we're currently on... 
            scontrol = (OneShotServoController*) scontrol->get_succ(); // next entry
            
            // disable if using the same servo so as to avoid mechanical confusion
            // or if this function is currently attached and running
            if (this == current || (current->m_servo == this->m_servo))
            {
              current->stop();
            }
            
	  }
	  
  	s_callbacksQueue.get_pred()->attach(this);	// attach to end of queue (linked back around)
  }
  
  
  /*
   * sets m_finished true if needs to be deactivated
   */ 
  void OneShotServoController::run() { 
  
  // update elapsed time
    m_elapsedTime = RTC::millis() - m_startTime;
    
    #if DEBUG
    trace << PSTR("run") << RTC::millis() << ':'
          << m_startTime << ':'
	  << m_elapsedTime
	  << endl;
    #endif
    
    // check if we've gone outside of our elapsed time. if so, stop.
    if ( m_elapsedTime >= m_duration)
    {
      percentFinished = 1;
      m_finished = true;
    }
    else
    {    	
      percentFinished = ((float)m_elapsedTime) / m_duration;
    }
    
    int newAngle = m_startAngle + int((m_endAngle-m_startAngle)*percentFinished);
    if (m_currentAngle != newAngle)
    {
        // DEBUG
        //trace << PSTR("newangle: ") << newAngle << endl;
	m_currentAngle = newAngle;
        m_servo->set_angle(m_currentAngle); 
    }
  }
  
  
/*
 * Update all servo callbacks
 *
 */
void OneShotServoController::update(uint32_t ms)
{
  // run through all callbacks for all servos and run their event handlers, remove if finished
  OneShotServoController* scontrol = (OneShotServoController*) s_callbacksQueue.get_succ();
  
  //trace << PSTR("update") << endl;
  
  // while not the 1st one
  while (scontrol != (OneShotServoController*) &s_callbacksQueue) 
  { 
        OneShotServoController* current = scontrol;
        // make sure not to detach the one we're currently on... 
        scontrol = (OneShotServoController*) scontrol->get_succ(); // next entry
        
	current->run();
        if (current->m_finished) current->stop();
  }
  
}

    
void OneShotServoController::Scheduler::run()
{
  //OneShotServoController::Scheduler::s_ms = RTC::millis();
  OneShotServoController::update(s_ms);
}  


