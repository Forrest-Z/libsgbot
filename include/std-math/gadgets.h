/* Created std-math/gadgets.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _STDM_GADGETS_H_
#define _STDM_GADGETS_H_

#include <cmath>
#include <type/pose2d.h>

namespace sgbot {
namespace math {

  float normalizeThetaValue(float theta);

  float normalizeTheta(float theta);

  template <typename T>
  inline T radianToDegree(const T radian)
  {
    return (radian * static_cast<T>(180.0f / M_PI));
  }

  template <typename T>
  inline T degreeToRadian(const T degree)
  {
    return (degree * static_cast<T>(M_PI / 180.0f));
  }

  bool farAwayBetweenPoses(const sgbot::Pose2D& p1, const sgbot::Pose2D& p2, float distance_diff, float theta_diff);

}  // namespace math  
}  // namespace sgbot

#endif  // _STDM_GADGETS_H_
