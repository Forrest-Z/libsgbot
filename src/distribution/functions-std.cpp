/* Created distribution/functions-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <distribution/functions.h>
#include <std-math/math.h>

namespace sgbot {
namespace distr {

  float logit(float p)
  {
    float s = p / (1.0f - p);
    return sgbot::math::log(s);
  }

  float logistic(float a)
  {
    float e = sgbot::math::exp(a);
    return (e / (e + 1.0f));
  }

}  // namespace distr
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
