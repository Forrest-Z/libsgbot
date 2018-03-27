/* Created type/rotation.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _TYPE_ROTATION_H_
#define _TYPE_ROTATION_H_

#include <common/exception.h>

namespace sgbot {

  class Rotation {
  public:
    Rotation()
      : roll_(0.0f), pitch_(0.0f), yaw_(0.0f)
    {}

    Rotation(float roll, float pitch, float yaw)
      : roll_(roll), pitch_(pitch), yaw_(yaw)
    {}
    
    virtual ~Rotation() {}

    void getRPY(float& roll, float& pitch, float& yaw) const
    {
      roll = roll_;
      pitch = pitch_;
      yaw = yaw_;
    }

    void setRPY(float roll, float pitch, float yaw)
    {
      roll_ = roll;
      pitch_ = pitch;
      yaw_ = yaw;
    }
    
  private:
    float roll_, pitch_, yaw_;
  };  // class Rotation

}  // namespace sgbot

#endif  // _TYPE_ROTATION_H_
