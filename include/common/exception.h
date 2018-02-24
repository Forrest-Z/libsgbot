/* Created common/exception.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <iostream>
#include <string>

namespace sgbot {

  class Exception: public std::exception {
  protected:
    std::string ex_what_;
  public:
    Exception(std::string ex_what)
      : ex_what_(ex_what) {}
    virtual ~Exception() throw() {}
    virtual const char* what() const throw() {
      return ex_what_.c_str();
    }
  };
  
}  // namespace sgbot

#endif  // _EXCEPTION_H_
