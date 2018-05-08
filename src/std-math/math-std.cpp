/* Created std-math/math-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <std-math/math.h>
#include <cstdlib>
#include <cmath>

namespace sgbot {
namespace math {
  
  int abs(int i)
  {
    return std::abs(i);
  }

  float fabs(float x)
  {
    return std::fabs(x);
  }

  long labs(long n)
  {
    return std::abs(n);
  }

  float exp(float x)
  {
    return std::exp(x);
  }

  float floor(float x)
  {
    return std::floor(x);
  }

  float ceil(float value)
  {
    return std::ceil(value);
  }

  float frexp(float value, int *eptr)
  {
    return std::frexp(value, eptr);
  }

  float ldexp(float value, int exp)
  {
    return std::ldexp(value, exp);
  }

  float log(float x)
  {
    return std::log(x);
  }

  float log10(float x)
  {
    return std::log10(x);
  }

  float pow(float x, float y)
  {
    return std::pow(x, y);
  }

  float pow10(int p)
  {
    return ::pow10(p);
  }

  float sqrt(float x)
  {
    return std::sqrt(x);
  }

  float acos(float x)
  {
    return std::acos(x);
  }

  float asin(float x)
  {
    return std::asin(x);
  }

  float atan(float x)
  {
    return std::atan(x);
  }

  float atan2(float y, float x)
  {
    return std::atan2(y, x);
  }

  float cos(float x)
  {
    return std::cos(x);
  }

  float sin(float x)
  {
    return std::sin(x);
  }

  float tan(float x)
  {
    return std::tan(x);
  }

  float cosh(float x)
  {
    return std::cosh(x);
  }

  float sinh(float x)
  {
    return std::sinh(x);
  }

  float tanh(float x)
  {
    return std::tanh(x);
  }

  float hypot(float x, float y)
  {
    return ::hypot(x, y);
  }

  float fmod(float x, float y)
  {
    return std::fmod(x, y);
  }

}  // namespace math
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
