/* Created type/velocity.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _TYPE_VELOCITY2D_H_
#define _TYPE_VELOCITY2D_H_

#include <common/exception.h>

namespace sgbot {

  class Velocity2D {
  public:
    Velocity2D()
      : linear(0), angular(0)
    {}
    
    virtual ~Velocity2D() {}
    
  public:
    float linear, angular;
  };  // class Velocity2D

}  // namespace sgbot

#endif  // _TYPE_VELOCITY2D_H_
