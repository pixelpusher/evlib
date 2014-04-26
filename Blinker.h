/**
 * @file Blinker.h
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
 * Blinks an output port (toggles between high/low) 
 * 
 */

#ifndef __COSA_BLINKER_HH__
#define __COSA_BLINKER_HH__

#include "Cosa/Periodic.hh"
#include "Cosa/OutputPin.hh"



class Blinker : public Periodic 
{  
public:
  Blinker(Board::DigitalPin pin, uint16_t ms, uint8_t initial = 0) : 
    Periodic(ms), m_pin(pin, initial) {}
  
  virtual void run() 
  { 
    // turn the LED on and off
    m_pin.toggle(); 
  }
  
  void period(uint16_t ms)
  {
  	end();
  	set_period(ms);
  	begin();
  }
  	
  
private:
  OutputPin m_pin;  // the pin (with an LED attached?)
};

#endif
