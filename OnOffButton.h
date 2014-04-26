/**
 * @file OnOffButton.h
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
 * Two very simple Button classes for detecting an input and turning another pin on/off
 *
 * @section TODO
 * integrate more functions from Wiring's Button class
 * 
 */

#ifndef __COSA_ONOFFBUTTON_HH__
#define __COSA_ONOFFBUTTON_HH__

#include "Cosa/Button.hh"
#include "Cosa/OutputPin.hh"


/*
 * Basic On-off button
 *
 */
 
class OnOffButton : public Button {

private:

  OutputPin onOffPin; // try an LED!
  
public:
  OnOffButton(Board::DigitalPin inPin, Board::DigitalPin outPin) : 
    Button(inPin, Button::ON_FALLING_MODE),  // falling mode means high to low  
    onOffPin(outPin)  // this controls the LED
  {  }

  virtual void on_change(uint8_t type)
  {
    onOffPin.toggle();  // turn the LED on or off    
  }  
};



/*
 * Faster On-off button
 *
 */

class FastOnOffButton : public Button {

private:

  OutputPin onOffPin; // try an LED!
  
public:
  FastOnOffButton(Board::DigitalPin inPin, Board::DigitalPin outPin) : 
    Button(inPin, Button::ON_FALLING_MODE),  // falling mode means high to low  
    onOffPin(outPin)  // this controls the LED
  {  }

  virtual void on_change(uint8_t type)
  {
    onOffPin.toggle();  // turn the LED on or off    
  }  
protected:
	static const uint16_t SAMPLE_MS = 16;    
  
};

#endif