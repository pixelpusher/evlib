/**
 *
 * @file SimpleServoController.h
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
 * This file is part of the evlib Arduino library and uses the Arduino Che Cosa project
 * by the talented Mikael Patel (and others)
 *
 * @section Description
 * Demonstration of the Servo control class.
 *
 * @section TODO
 * Add some protection to start and stop angle functions. Exception handling?
 */
 
#ifndef __SIMPLESERVOONESHOT_HH__
#define __SIMPLESERVOONESHOT_HH__

#include <Oneshot.h>


// Blinking LED output pin
class SimpleServoController : public Oneshot {

public:

  SimpleServoController(Servo& servo) : 
    Oneshot(), m_servo(&servo) {}
  
  virtual void run() { 
	int newAngle = m_startAngle + int((m_endAngle-m_startAngle)*percentFinished);
  	if (m_currentAngle != newAngle)
  	{
	  	m_currentAngle = newAngle;
  		m_servo->set_angle(m_currentAngle); 
  	}
  }
  
  /**
   * Set the reference to the servo to control
   */
  SimpleServoController& startAngle(int _startAngle)
  {
  	m_startAngle = _startAngle;
  	return *this;
  }

  /**
   * Set the reference to the servo to control
   */
  SimpleServoController& endAngle(int _endAngle)
  {
  	m_endAngle = _endAngle;
  	return *this;
  }

  /**
   * Set the reference to the servo to control
   */

  SimpleServoController& servo(Servo* _servo)
  {
  	m_servo = _servo;
  }
  

private:
  Servo* m_servo;
  int m_startAngle;
  int m_endAngle;
  int m_currentAngle;
};

#endif
