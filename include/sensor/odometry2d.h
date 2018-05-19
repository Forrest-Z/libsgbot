/* Created sensor/odometry2d.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SENSOR_ODOMETRY2D_H_
#define _SENSOR_ODOMETRY2D_H_

#include <vector>
#include <std-math/math.h>
#include <type/rotation.h>

namespace sgbot {
namespace sensor {
  
  class Odometry2D {
  public:
    Odometry2D()
      : x_(0.0f), y_(0.0f), theta_(0.0f)
    {}

    virtual ~Odometry2D() {}

  private:
    float x_, y_, theta_;
  };  //class Odometry2D
  
}  // namespace sgbot
}  // namespace sensor

#endif  // _SENSOR_ODOMETRY2D_H_
