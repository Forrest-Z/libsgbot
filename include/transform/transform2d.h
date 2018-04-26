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
      translate_ = tf.translate_;
      rotate_ = tf.rotate_;
      scale_ = tf.scale_;
      tf_ = tf.tf_;
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

      result.translate_ = result.translate_ * tf.translate_;
      result.rotate_ = result.rotate_ * tf.rotate_;
      result.scale_ = result.scale_ * tf.scale_;
      result.tf_ = result.tf_ * tf.tf_;

      return result;
    }

    Transform2D operator *(const Transform2D& tf) const
    {
      Transform2D result(*this);

      result.translate_ = result.translate_ * tf.translate_;
      result.rotate_ = result.rotate_ * tf.rotate_;
      result.scale_ = result.scale_ * tf.scale_;
      result.tf_ = result.tf_ * tf.tf_;

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
      getTranslation(dx, dy);
      theta = getRotate();
      scalar = getScalar();
    }

    sgbot::la::Matrix<float, 3, 3> getMatrix() const
    {
      return tf_;
    }

    // Get a inverse transform
    Transform2D inverse() const
    {
      //return Transform2D(-dx_, -dy_, -theta_, (1.0f / scalar_));
      Transform2D inv;
      inv.translate_ = this->translate_.inverse();
      inv.translate_ = this->rotate_.inverse();
      inv.translate_ = this->scale_.inverse();
      //inv.calcTransformMatrix();
      inv.tf_ = this->tf_.inverse();
      return inv;
    }

    // To transform a pose in origin frame
    sgbot::Pose2D transform(const sgbot::Pose2D& pose);

    sgbot::Point2D transform(const sgbot::Point2D& point);

  protected:

    void setScalar(const float scalar)
    {
      scale_(0, 0) = scalar;
      scale_(1, 1) = scalar;
      scale_(2, 2) = 1.0f;
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
    }

    void setTranslate(const float dx, const float dy)
    {
      translate_(0, 0) = 1.0f;
      translate_(0, 2) = dx;
      translate_(1, 1) = 1.0f;
      translate_(1, 2) = dy;
      translate_(2, 2) = 1.0f;
    }

    const float getScalar() const
    {
      assert(scale_(0, 0) == scale_(1, 1));
      return scale_(0, 0);
    }

    const float getRotate() const
    {
      assert(rotate_(0, 0) == rotate_(1, 1));
      assert(rotate_(0, 1) == -rotate_(1, 0));

      return sgbot::math::asin(rotate_(0, 1));
    }

    void getTranslation(float& dx, float& dy) const
    {
      dx = translate_(0, 2);
      dy = translate_(1, 2);
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
    
  };  // class Transform2D

}  // namespace tf
}  // namespace sgbot

#endif  // _TF_TRANSFORM2D_H_
