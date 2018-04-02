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

namespace sgbot {

  class Pose2D {
  public:
    Pose2D()
      : x(0), y(0), theta(0)
    {}

    Pose2D(float px, float py, float ptheta)
      : x(px), y(py), theta(ptheta)
    {}
    
    virtual ~Pose2D() {}
    
  public:
    float x, y, theta;
  };  // class Pose2D
/*
  std::ostream& operator <<(std::ostream& output, const Pose2D& pose)
  {
    output << std::endl;
    output << "[";
    output << std::fixed << std::setprecision(2) << pose.x << ", " << pose.y << ", " << pose.theta << ", " << std::endl;
    output << "]" << std::endl;
  }
*/

}  // namespace sgbot

#endif  // _TYPE_POSE2D_H_
