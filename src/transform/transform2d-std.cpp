/* Created transform/transform2d-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <transform/transform2d.h>
#include <std-math/math.h>

namespace sgbot {
namespace tf {

  sgbot::Pose2D Transform2D::transform(const sgbot::Pose2D& pose)
  {
    sgbot::Pose2D result;

    sgbot::Point2D point;
    point.x() = pose.x();
    point.y() = pose.y();
    
    point = transform(point);

    result.x() = point.x();
    result.y() = point.y();
    result.theta() = pose.theta() + tf_(2);

    return result;
  }

  sgbot::Point2D Transform2D::transform(const sgbot::Point2D& point)
  {
    sgbot::Point2D result;

    float cos_val = sgbot::math::cos(tf_(2));
    float sin_val = sgbot::math::sin(tf_(2));

    result.x() = point.x() * cos_val - point.y() * sin_val + tf_(0);
    result.y() = point.x() * sin_val + point.y() * cos_val + tf_(1);

    return result;
  }

}  // namespace tf
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
