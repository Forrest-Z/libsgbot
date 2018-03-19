/* Created distribution/gaussian-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <distribution/gaussian.h>

namespace sgbot {
namespace distr {

  template <typename T, size_t Dimension>
  bool Gaussian<T, Dimension>::sample(std::vector<Vector<T, Dimension> >& samples, const size_t numbers)
  {

  }

  template <typename T, size_t Dimension>
  bool Gaussian<T, Dimension>::sample(Vector<T, Dimension>& one_sample)
  {

  }

  template <typename T, size_t Dimension>
  double Gaussian<T, Dimension>::probability(const Vector<T, Dimension> value)
  {

  }

}  // namespace distr
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
