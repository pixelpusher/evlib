/**
 * @file OneshotButton.h
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
 * A one-shot button that triggers a ControlAction when 'pressed'
 *
 * @section TODO
 * integrate more functions from Wiring's Button class
 * 
 */
 
#ifndef __BUTTONONESHOT_HH__
#define __BUTTONONESHOT_HH__

#include "Cosa/Button.hh"
//#include "Cosa/OutputPin.hh"

#include <ControlAction.h>


// for debugging
#if DEBUG
#include "Cosa/Trace.hh"
#include "Cosa/IOStream/Driver/UART.hh"
#endif


class OneshotButton : public Button {
public:

  /**
   * Button change detection modes; falling (high to low), rising (low
   * to high) and change (falling or rising). 
   *
   * ON_FALLING_MODE = 0,
   * ON_RISING_MODE = 1,
   * ON_CHANGE_MODE = 2
   */

  OneshotButton(Board::DigitalPin pin, ControlAction& action) : 
    Button(pin, Button::ON_FALLING_MODE), 
    m_action(&action)  // any change, high or low  
    //led(Board::LED)
  {}

  /*
   * When the button is pressed, start the action
   */
  virtual void on_change(uint8_t type)
  {
    //led.toggle();
    m_action->start(); 

    #if DEBUG
    trace << PSTR("pushed: ")
	<< endl; 
    #endif
  }  
  
  
  
private:
  ControlAction* m_action;
  //OutputPin led;
};


#endif
