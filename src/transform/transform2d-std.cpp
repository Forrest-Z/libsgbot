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
    result.theta() = pose.theta() + getRotate();

    return result;
  }

  sgbot::Point2D Transform2D::transform(const sgbot::Point2D& point)
  {
    sgbot::Point2D result;

    sgbot::la::Vector<float, 3> coord;

    coord = tf_ * point.vectorForTransform();

    result.x() = coord(0);
    result.y() = coord(1);

    return result;
  }

}  // namespace tf
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
