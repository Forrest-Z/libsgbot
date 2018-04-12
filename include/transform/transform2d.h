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
      setValue(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Transform2D(float dx, float dy, float theta, float scalar)
    {
      setValue(dx, dy, theta, scalar);
    }

    // Define destructor
    virtual ~Transform2D() {}

    // Copy constructor
    Transform2D(const Transform2D& tf)
    {
      float x, y, theta, scalar;
      tf.getValue(x, y, theta, scalar);
      setValue(x, y, theta, scalar);
    }

    Transform2D& operator()(float dx, float dy, float theta, float scalar)
    {
      Transform2D& tf = *this;
      tf.setValue(dx, dy, theta, scalar);
      return tf;
    }
    
    Transform2D operator()(float x, float y, float theta, float scalar) const
    {
      Transform2D tf(*this);
      tf.setValue(x, y, theta, scalar);
      return tf;
    }

    // Transform operations
    Transform2D& operator *=(const Transform2D& tf)
    {
      Transform2D& result = *this;

      assert(result.scalar_ == tf.scalar_);

      float dx, dy, theta;

      dx = result.dx_ + tf.dx_;
      dy = result.dy_ + tf.dy_;
      theta = result.theta_ + tf.theta_;

      result.setValue(dx, dy, theta, result.scalar_);

      return result;
    }

    Transform2D operator *(const Transform2D& tf) const
    {
      Transform2D result(*this);

      assert(result.scalar_ == tf.scalar_);

      float dx, dy, theta;

      dx = result.dx_ + tf.dx_;
      dy = result.dy_ + tf.dy_;
      theta = result.theta_ + tf.theta_;

      result.setValue(dx, dy, theta, result.scalar_);

      return result;
    }

    // Member functions
    void setValue(float dx, float dy, float theta, float scalar)
    {
      setScalar(scalar);
      setTranslate(dx, dy);
      setRotate(theta);
      calcTransformMatrix();
    }

    void getValue(float& dx, float& dy, float& theta, float& scalar) const
    {
      dx = dx_;
      dy = dy_;
      theta = theta_;
      scalar = scalar_;
    }

    // Get a inverse transform
    Transform2D inverse() const
    {
      return Transform2D(-dx_, -dy_, -theta_, (1.0f / scalar_));
    }

    // To transform a pose in origin frame
    sgbot::Pose2D transform(const sgbot::Pose2D& pose);

    sgbot::Point2D transform(const sgbot::Point2D& point);

  private:

    void setScalar(const float scalar)
    {
      scale_(0, 0) = scalar;
      scale_(1, 1) = scalar;
      scale_(2, 2) = 1.0f;

      scalar_ = scalar;
    }

    void setRotate(const float theta)
    {
      float sin_val = sgbot::math::sin(theta);
      float cos_val = sgbot::math::cos(theta);
      rotate_(0, 0) = cos_val;
      rotate_(0, 1) = -sin_val;
      rotate_(1, 0) = sin_val;
      rotate_(1, 1) = cos_val;
      rotate_(2, 2) = 1.0f;

      theta_ = theta;
    }

    void setTranslate(const float dx, const float dy)
    {
      translate_(0, 0) = 1.0f;
      translate_(0, 2) = dx;
      translate_(1, 1) = 1.0f;
      translate_(1, 2) = dy;
      translate_(2, 2) = 1.0f;

      dx_ = dx;
      dy_ = dy;
    }

    void calcTransformMatrix()
    {
      tf_ = translate_ * rotate_ * scale_;
    }

  protected:
    sgbot::la::Matrix<float, 3, 3> translate_;
    sgbot::la::Matrix<float, 3, 3> rotate_;
    sgbot::la::Matrix<float, 3, 3> scale_;

    sgbot::la::Matrix<float, 3, 3> tf_;

    float dx_, dy_;
    float theta_;
    float scalar_;
    
  };  // class Transform2D

}  // namespace tf
}  // namespace sgbot

#endif  // _TF_TRANSFORM2D_H_
