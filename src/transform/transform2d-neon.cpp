/* Created transform/transform2d-neon.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_ARM_NEON_

#include <transform/transform2d.h>

namespace sgbot {
namespace tf {
  Transform2D& Transform2D::operator *=(const Transform2D& tf) {

  }

  Transform2D Transform2D::operator *(const Transform2D& tf) {

  }

  Transform2D Transform2D::inverse() {

  }

  Pose2D Transform2D::transform(const Pose2D pose) {

  }

}  // namespace tf
}  // namespace sgbot

#endif  // _USE_ARM_NEON_
