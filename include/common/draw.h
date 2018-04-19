/* Created common/draw.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _DRAW_H_
#define _DRAW_H_

#include <exception>
#include <iostream>
#include <string>
#include <type/point2d.h>
#include <type/pose2d.h>

namespace sgbot {

  class Draw {
  public:
    Draw()
    {}

    virtual ~Draw()
    {}

  private:

  };  // class Debug
  
  Draw* draw;
}  // namespace sgbot

#endif  // _DRAW_H_
