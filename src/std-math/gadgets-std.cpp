/* Created std-math/gadgets-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <std-math/gadgets.h>
#include <cstdlib>

namespace sgbot {
namespace math {
  
  float normalizeThetaValue(float theta)
  {
    float pi2 = 2.0f * M_PI;
    return sgbot::math::fmod(sgbot::math::fmod(theta, pi2) + pi2, pi2);
  }

  float normalizeTheta(float theta)
  {
    float a = normalizeThetaValue(theta);
    if(a > M_PI)
    {
      a -= 2.0f * M_PI;
    }
    return a;
  }

  bool farAwayBetweenPoses(const sgbot::Pose2D& p1, const sgbot::Pose2D& p2, float distance_diff, float theta_diff)
  {
    // TODO: not implement
  }

}  // namespace math
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
