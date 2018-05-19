/* Created distribution/base.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _DISTRIBUTION_BASE_H_
#define _DISTRIBUTION_BASE_H_

#include <vector>
#include <common/exception.h>
#include <linear-algebra/vector.h>
#include <linear-algebra/matrix.h>

namespace sgbot {
namespace distr {

  using namespace sgbot::la;

  template <size_t Dimension>
  class Distribution {
  public:
    Distribution() {
    }

    virtual ~Distribution() {}

    // Member functions
    size_t dimensions() {
      return Dimension;
    }

    virtual bool sample(std::vector<Vector<float, Dimension> >& samples, const size_t numbers) = 0;

    virtual bool sample(Vector<float, Dimension>& one_sample) = 0;

    virtual float probability(const Vector<float, Dimension> value) = 0;
  
  protected:

    // Members access functions for inherit classes
    void getValue(Vector<float, Dimension>& mu, Matrix<float, Dimension, Dimension>& sigma) {
      mu = mu_;
      sigma = sigma_;
    }

    void setValue(Vector<float, Dimension> mu, Matrix<float, Dimension, Dimension> sigma) {
      mu_ = mu;
      sigma_ = sigma;
    }

  private:
    Vector<float, Dimension> mu_;
    Matrix<float, Dimension, Dimension> sigma_;
  };  // class Distribution
}  // namespace distr
}  // namespace sgbot

#endif  // _DISTRIBUTION_BASE_H_
