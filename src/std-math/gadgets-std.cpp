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
    if(distance(p1, p2) > distance_diff)
    {
      return true;
    }

    float delta_theta = p1.theta() - p2.theta();

    if(delta_theta > M_PI)
    {
      delta_theta -= M_PI * 2.0f;
    }
    else if(delta_theta < -M_PI)
    {
      delta_theta += M_PI * 2.0f;
    }

    if(sgbot::math::fabs(delta_theta) > theta_diff)
    {
      return true;
    }

    return false;
  }

}  // namespace math
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
