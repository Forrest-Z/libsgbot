/* Created std-math/math.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _STDM_MATH_H_
#define _STDM_MATH_H_

namespace sgbot {
namespace math {

  int abs(int i);

  float cabs(float a, float b);

  float fabs(float x);

  long labs(long n);

  float exp(float x);

  float floor(float x);

  float ceil(float value);

  float frexp(float value, int *eptr);

  float ldexp(float value, int exp);

  float log(float x);

  float log10(float x);

  float pow(float x, float y);

  float pow10(int p);

  float sqrt(float x);

  float acos(float x);

  float asin(float x);

  float atan(float x);

  float atan2(float y, float x);

  float cos(float x);

  float sin(float x);

  float tan(float x);

  float cosh(float x);

  float sinh(float x);

  float tanh(float x);

  float hypot(float x, float y);

  float fmod(float x, float y);

  inline int sign(int n)
  {
    return (n > 0) ? 1 : -1;
  }

  inline float sqr(float x)
  {
    return (x * x);
  }

}  // namespace math  
}  // namespace sgbot

#endif  // _STDM_MATH_H_
