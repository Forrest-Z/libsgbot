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

  double fabs(double x)
  {
    return ::fabs(x);
  }

  long labs(long n)
  {
    return ::abs(n);
  }

  double exp(double x)
  {
    return ::exp(x);
  }

  double floor(double x)
  {
    return ::floor(x);
  }

  double ceil(double value)
  {
    return ::ceil(value);
  }

  double frexp(double value, int *eptr)
  {
    return ::frexp(value, eptr);
  }

  double ldexp(double value, int exp)
  {
    return ::ldexp(value, exp);
  }

  double log(double x)
  {
    return ::log(x);
  }

  double log10(double x)
  {
    return ::log10(x);
  }

  double pow(double x, double y)
  {
    return ::pow(x, y);
  }

  double pow10(int p)
  {
    return ::pow10(p);
  }

  double sqrt(double x)
  {
    return ::sqrt(x);
  }

  double acos(double x)
  {
    return ::acos(x);
  }

  double asin(double x)
  {
    return ::asin(x);
  }

  double atan(double x)
  {
    return ::atan(x);
  }

  double atan2(double y, double x)
  {
    return ::atan2(y, x);
  }

  double cos(double x)
  {
    return ::cos(x);
  }

  double sin(double x)
  {
    return ::sin(x);
  }

  double tan(double x)
  {
    return ::tan(x);
  }

  double cosh(double x)
  {
    return ::cosh(x);
  }

  double sinh(double x)
  {
    return ::sinh(x);
  }

  double tanh(double x)
  {
    return ::tanh(x);
  }

  double hypot(double x, double y)
  {
    return ::hypot(x, y);
  }

}  // namespace math
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
