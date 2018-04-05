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
#include <linear-algebra/vector.h>

namespace sgbot {

  class Point2D {
  public:
    Point2D()
      : x(point_(0)), y(point_(1))
    {
    }
    
    virtual ~Point2D() {}
   
    // Copy constructor
    Point2D(const Point2D& other)
      : x(point_(0)), y(point_(1))
    {
      x = other.x;
      y = other.y;
    }

    Point2D& operator =(const Point2D& other)
    {
      x = other.x;
      y = other.y;
      return *this;
    }
    
  public:
    float& x, y;

  private:
    sgbot::la::Vector<float, 2> point_;
  };  // class Point2D

}  // namespace sgbot

#endif  // _TYPE_POINT2D_H_
