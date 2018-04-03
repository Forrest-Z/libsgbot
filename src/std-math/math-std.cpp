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
    return ::abs(i);
  }

  float fabs(float x)
  {
    return ::fabs(x);
  }

  long labs(long n)
  {
    return ::abs(n);
  }

  float exp(float x)
  {
    return ::exp(x);
  }

  float floor(float x)
  {
    return ::floor(x);
  }

  float ceil(float value)
  {
    return ::ceil(value);
  }

  float frexp(float value, int *eptr)
  {
    return ::frexp(value, eptr);
  }

  float ldexp(float value, int exp)
  {
    return ::ldexp(value, exp);
  }

  float log(float x)
  {
    return ::log(x);
  }

  float log10(float x)
  {
    return ::log10(x);
  }

  float pow(float x, float y)
  {
    return ::pow(x, y);
  }

  float pow10(int p)
  {
    return ::pow10(p);
  }

  float sqrt(float x)
  {
    return ::sqrt(x);
  }

  float acos(float x)
  {
    return ::acos(x);
  }

  float asin(float x)
  {
    return ::asin(x);
  }

  float atan(float x)
  {
    return ::atan(x);
  }

  float atan2(float y, float x)
  {
    return ::atan2(y, x);
  }

  float cos(float x)
  {
    return ::cos(x);
  }

  float sin(float x)
  {
    return ::sin(x);
  }

  float tan(float x)
  {
    return ::tan(x);
  }

  float cosh(float x)
  {
    return ::cosh(x);
  }

  float sinh(float x)
  {
    return ::sinh(x);
  }

  float tanh(float x)
  {
    return ::tanh(x);
  }

  float hypot(float x, float y)
  {
    return ::hypot(x, y);
  }

}  // namespace math
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
