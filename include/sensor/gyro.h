/* Created sensor/gyro.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _SENSOR_GYRO_H_
#define _SENSOR_GYRO_H_

#include <vector>
#include <std-math/math.h>
#include <type/rotation.h>

namespace sgbot {
namespace sensor {
  
  class Gyro {
  public:
    Gyro()
      : rotation_(0.0f, 0.0f, 0.0f)
    {}

    virtual ~Gyro() {}

  private:
    sgbot::Rotation rotation_;
  };  //class Gyro
  
}  // namespace sgbot
}  // namespace sensor

#endif  // _SENSOR_GYRO_H_
