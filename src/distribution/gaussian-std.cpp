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

  template <size_t Dimension>
  bool Gaussian<Dimension>::sample(std::vector<Vector<float, Dimension> >& samples, const size_t numbers)
  {

  }

  template <size_t Dimension>
  bool Gaussian<Dimension>::sample(Vector<float, Dimension>& one_sample)
  {

  }

  template <size_t Dimension>
  float Gaussian<Dimension>::probability(const Vector<float, Dimension> value)
  {

  }

}  // namespace distr
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
