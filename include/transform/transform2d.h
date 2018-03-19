/* Created transform/transform2d.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _TF_TRANSFORM2D_H_
#define _TF_TRANSFORM2D_H_

#include <common/exception.h>
#include <linear-algebra/matrix.h>
#include <linear-algebra/vector.h>
#include <type/pose2d.h>
#include <type/point2d.h>

namespace sgbot {
namespace tf {

  using namespace sgbot::la;

  class Transform2D {
  public:
    // Define constructor
    Transform2D()
      : x_(0), y_(0), theta_(0)
    {}

    // Define destructor
    virtual ~Transform2D() {}

    // Copy constructor
    Transform2D(const Transform2D& tf) {}

  public:
    // Copy operator
    Transform2D& operator()(double x, double y, double theta) {

    }
    
    Transform2D operator()(double x, double y, double theta) const {

    }

    // Transform operations
    Transform2D& operator *=(const Transform2D& tf);
    Transform2D operator *(const Transform2D& tf);

    // Member functions
    void setValue(double x, double y, double theta)
    {
      x_ = x;
      y_ = y;
      theta_ = theta;
    }

    void getValue(double& x, double& y, double& theta)
    {
      x = x_;
      y = y_;
      theta = theta_;
    }

    // Get a inverse transform
    Transform2D inverse();

    // To transform a pose in origin frame
    sgbot::Pose2D transform(const sgbot::Pose2D& pose);

    sgbot::Point2D transform(const sgbot::Point2D& point);
    

  private:
    double x_, y_, theta_;
  };  // class Transform2D

}  // namespace tf
}  // namespace sgbot

#endif  // _TF_TRANSFORM2D_H_
