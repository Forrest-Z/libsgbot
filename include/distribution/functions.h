/* Created distribution/functions.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _DISTRIBUTION_FUNCTIONS_H_
#define _DISTRIBUTION_FUNCTIONS_H_

#include <common/exception.h>

namespace sgbot {
namespace distr {

  float logit(float p);

  float logistic(float a);

}  // namespace distr
}  // namespace sgbot

#endif  // _DISTRIBUTION_FUNCTIONS_H_
