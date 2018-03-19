/* Created type/point2d.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _TYPE_POINT2D_H_
#define _TYPE_POINT2D_H_

#include <common/exception.h>

namespace sgbot {

  class Point2D {
  public:
    Point2D()
      : x(0), y(0)
    {}
    
    virtual ~Point2D() {}
    
  public:
    float x, y;
  };  // class Point2D

}  // namespace sgbot

#endif  // _TYPE_POINT2D_H_
