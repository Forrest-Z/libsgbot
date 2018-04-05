/* Created type/pose2d.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _TYPE_POSE2D_H_
#define _TYPE_POSE2D_H_

#include <common/exception.h>
#include <iomanip>
#include <linear-algebra/vector.h>
#include <std-math/math.h>

namespace sgbot {

  class Pose2D {
  public:
    Pose2D()
      : x(point_(0)), y(point_(1)), theta(0)
    {
    }

    Pose2D(float px, float py, float ptheta)
      : x(point_(0)), y(point_(1)), theta(ptheta)
    {
      x = px;
      y = py;
    }
    
    virtual ~Pose2D() {}

    // Copy constructor
    Pose2D(const Pose2D& other)
      : x(point_(0)), y(point_(1))
    {
      x = other.x;
      y = other.y;
      theta = other.theta;
    }

    Pose2D& operator =(const Pose2D& other)
    {
      x = other.x;
      y = other.y;
      theta = other.theta;
      return *this;
    }
    
  public:
    float& x, y;
    float theta;

  private:
    sgbot::la::Vector<float, 2> point_;

  };  // class Pose2D

  inline std::ostream& operator <<(std::ostream& output, const Pose2D& pose)
  {
    output << std::endl;
    output << "[";
    output << std::fixed << std::setprecision(2) << pose.x << ", " << pose.y << ", " << pose.theta;
    output << "]" << std::endl;
    return output;
  }

}  // namespace sgbot

#endif  // _TYPE_POSE2D_H_
