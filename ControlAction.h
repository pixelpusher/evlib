/**
 *
 * @file ControlAction.h
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
 * ControlAction class to be attached to buttons, then triggered when 'pressed'
 *
 */
 
#ifndef __CONTROLACTION_HH__
#define __CONTROLACTION_HH__

#include "Cosa/Linkage.hh"


class ControlAction : protected Link {

public:

  /*  
   * start the action
   */
  virtual void start() = 0;
  
  /**
   * stop the action
   */
  virtual void stop() = 0;
  
};

#endif
