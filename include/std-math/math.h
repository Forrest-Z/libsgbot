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

  double cabs(double a, double b);

  double fabs(double x);

  long labs(long n);

  double exp(double x);

  double floor(double x);

  double ceil(double value);

  double frexp(double value, int *eptr);

  double ldexp(double value, int exp);

  double log(double x);

  double log10(double x);

  double pow(double x, double y);

  double pow10(int p);

  double sqrt(double x);

  double acos(double x);

  double asin(double x);

  double atan(double x);

  double atan2(double y, double x);

  double cos(double x);

  double sin(double x);

  double tan(double x);

  double cosh(double x);

  double sinh(double x);

  double tanh(double x);

  double hypot(double x, double y);

}  // namespace math  
}  // namespace sgbot

#endif  // _STDM_MATH_H_
