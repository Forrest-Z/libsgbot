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

    Transform2D(float x, float y, float theta)
      : x_(x), y_(y), theta_(theta)
    {}

    // Define destructor
    virtual ~Transform2D() {}

    // Copy constructor
    Transform2D(const Transform2D& tf)
    {
      float x, y, theta;
      tf.getValue(x, y, theta);
      setValue(x, y, theta);
    }

    // Copy operator
    Transform2D& operator()(float x, float y, float theta)
    {
      Transform2D& tf = *this;
      tf.setValue(x, y, theta);
      return tf;
    }
    
    Transform2D operator()(float x, float y, float theta) const
    {
      Transform2D tf(*this);
      tf.setValue(x, y, theta);
      return tf;
    }

    // Transform operations
    Transform2D& operator *=(const Transform2D& tf)
    {
      Transform2D& result = *this;

      float x0, y0, theta0;

      float x1, y1, theta1;

      result.getValue(x0, y0, theta0);

      tf.getValue(x1, y1, theta1);

      result.setValue(x0 + x1, y0 + y1, theta0 + theta1);

      return result;
    }

    Transform2D operator *(const Transform2D& tf) const
    {
      Transform2D result(*this);

      float x0, y0, theta0;

      float x1, y1, theta1;

      result.getValue(x0, y0, theta0);

      tf.getValue(x1, y1, theta1);

      result.setValue(x0 + x1, y0 + y1, theta0 + theta1);

      return result;
    }

    // Member functions
    void setValue(float x, float y, float theta)
    {
      x_ = x;
      y_ = y;
      theta_ = theta;
    }

    void getValue(float& x, float& y, float& theta) const
    {
      x = x_;
      y = y_;
      theta = theta_;
    }

    // Get a inverse transform
    Transform2D inverse() const
    {
      Transform2D result(-x_, -y_, (theta_ + 180));
    }

    // To transform a pose in origin frame
    sgbot::Pose2D transform(const sgbot::Pose2D& pose);

    sgbot::Point2D transform(const sgbot::Point2D& point);
    

  private:
    float x_, y_, theta_;
  };  // class Transform2D

}  // namespace tf
}  // namespace sgbot

#endif  // _TF_TRANSFORM2D_H_
