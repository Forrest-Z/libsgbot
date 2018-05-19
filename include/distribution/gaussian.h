/* Created distribution/gaussian.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _DISTRIBUTION_GAUSSION_H_
#define _DISTRIBUTION_GAUSSION_H_

#include "base.h"

namespace sgbot {
namespace distr {

  template <size_t Dimension>
  class Gaussian: public Distribution<Dimension> {
  public:
    Gaussian() {

    }

    virtual ~Gaussian() {}

    // Member functions

    virtual bool sample(std::vector<Vector<float, Dimension> >& samples, const size_t numbers);

    virtual bool sample(Vector<float, Dimension>& one_sample);

    virtual float probability(const Vector<float, Dimension> value);
  
  };  // class Gaussian
}  // namespace distr
}  // namespace sgbot

#endif  // _DISTRIBUTION_GAUSSION_H_
