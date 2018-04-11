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

  class Transform2D {
  public:
    // Define constructor
    Transform2D()
    {
      tf_(0) = 0.0f;
      tf_(1) = 0.0f;
      tf_(2) = 0.0f;
    }

    Transform2D(float x, float y, float theta)
    {
      tf_(0) = x;
      tf_(1) = y;
      tf_(2) = theta;
    }

    // Define destructor
    virtual ~Transform2D() {}

    // Copy constructor
    Transform2D(const Transform2D& tf)
    {
      float x, y, theta;
      tf.getValue(x, y, theta);
      setValue(x, y, theta);
    }

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

      result.tf_ += tf.tf_;

      return result;
    }

    Transform2D operator *(const Transform2D& tf) const
    {
      Transform2D result(*this);

      result.tf_ += tf.tf_;

      return result;
    }

    // Member functions
    void setValue(float x, float y, float theta)
    {
      tf_(0) = x;
      tf_(1) = y;
      tf_(2) = theta;
    }

    void getValue(float& x, float& y, float& theta) const
    {
      x = tf_(0);
      y = tf_(1);
      theta = tf_(2);
    }

    // Get a inverse transform
    Transform2D inverse() const
    {
      return Transform2D(-tf_(0), -tf_(1), (tf_(2) + 180));
    }

    // To transform a pose in origin frame
    sgbot::Pose2D transform(const sgbot::Pose2D& pose);

    sgbot::Point2D transform(const sgbot::Point2D& point);

  protected:
    sgbot::la::Vector<float 3> translation_;
    sgbot::la::Matrix<float, 3, 3> rotation_;
    sgbot::la::Vector<float, 3> scaling_;
    
  };  // class Transform2D

}  // namespace tf
}  // namespace sgbot

#endif  // _TF_TRANSFORM2D_H_
