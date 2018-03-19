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

namespace sgbot {

  class Pose2D {
  public:
    Pose2D()
      : x(0), y(0), theta(0)
    {}
    
    virtual ~Pose2D() {}
    
  public:
    float x, y, theta;
  };  // class Pose2D

}  // namespace sgbot

#endif  // _TYPE_POSE2D_H_
