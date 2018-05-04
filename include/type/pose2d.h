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
#include <type/point2d.h>

namespace sgbot {

  class Pose2D {
  public:
    Pose2D()
    {
      pose_(0) = 0.0f;
      pose_(1) = 0.0f;
      pose_(2) = 0.0f;
    }

    Pose2D(float px, float py, float ptheta)
    {
      pose_(0) = px;
      pose_(1) = py;
      pose_(2) = ptheta;
    }
    
    virtual ~Pose2D() {}

    // Copy constructor
    Pose2D& operator =(const Pose2D& other)
    {
      pose_(0) = other.x();
      pose_(1) = other.y();
      pose_(2) = other.theta();
      return *this;
    }

    Pose2D& operator *=(float factor)
    {
      pose_(0) *= factor;
      pose_(1) *= factor;
      return *this;
    }

    Pose2D& operator /=(float factor)
    {
      pose_(0) /= factor;
      pose_(1) /= factor;
      return *this;
    }
    
    float& x()
    {
      return pose_(0);
    }

    const float x() const
    {
      return pose_(0);
    }

    float& y()
    {
      return pose_(1);
    }

    const float y() const
    {
      return pose_(1);
    }

    float& theta()
    {
      return pose_(2);
    }

    const float theta() const
    {
      return pose_(2);
    }

    const Point2D point() const
    {
      Point2D p;
      p.x() = pose_(0);
      p.y() = pose_(1);
      return p;
    }

  private:
    sgbot::la::Vector<float, 3> pose_;
  };  // class Pose2D

  inline std::ostream& operator <<(std::ostream& output, const Pose2D& pose)
  {
    output << std::endl;
    output << "[";
    output << std::fixed << std::setprecision(2) << pose.x() << ", " << pose.y() << ", " << pose.theta();
    output << "]" << std::endl;
    return output;
  }

  inline float distance(const Pose2D& p1, const Pose2D& p2)
  {
    sgbot::la::Vector<float, 2> v1, v2;
    
    v1(0) = p1.x();
    v1(1) = p1.y();

    v2(0) = p2.x();
    v2(1) = p2.y();

    return (v1 - v2).length();
  }

}  // namespace sgbot

#endif  // _TYPE_POSE2D_H_
