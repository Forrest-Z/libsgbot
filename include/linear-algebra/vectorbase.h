/* Created linear-algebra/vectorbase.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _LA_VECTORBASE_H_
#define _LA_VECTORBASE_H_

#include <common/exception.h>
#include <vector>

namespace sgbot {
namespace la {
  /*
  class VectorException: public sgbot::Exception {
  private:
    
  public:
    VectorException(std::string ex_what)
      : ex_what_(ex_what) {}
    virtual ~VectorException() throw() {}
  };
  */
  
  typedef std::vector<double> VectorArray;

  class VectorBase {
  public:
    // Define Constructors
    VectorBase()
    {}

    VectorBase(size_t size)
    {
      vector_.resize(size);
    }

    // Define Destructor
    virtual ~VectorBase() {}

    // Copy constructor
    VectorBase(const VectorBase& vector)
    {
    }

    VectorBase operator =(const VectorBase& other) const
    {

    }

    VectorBase& operator =(const VectorBase& other)
    {

    }

    // Member functions
    
    size_t getItemCount() {
      return vector_.size();
    }

    // Copy operator
    virtual double& operator()(size_t index) {

    }
    
    virtual double operator()(size_t index) const {

    }

    // Vector monocular operators
    virtual VectorBase operator -() const;

    // Vector scale operators
    virtual VectorBase& operator *=(const double scalar);
    virtual VectorBase& operator /=(const double scalar);

    virtual VectorBase operator *(const double scalar) const;
    virtual VectorBase operator /(const double scalar) const;

    // Vector math operators
    virtual VectorBase& operator +=(const VectorBase& vector);
    virtual VectorBase& operator -=(const VectorBase& vector);

    virtual VectorBase operator +(const VectorBase& vector) const;
    virtual VectorBase operator -(const VectorBase& vector) const;

    // Vector compare operators
    virtual bool operator ==(const VectorBase& vector) const;
    virtual bool operator !=(const VectorBase& vector) const;

    // Vector other operators
    virtual double length() const;
    virtual double normalize() const;
    virtual double dot() const;
    virtual VectorBase cross(const VectorBase& vector) const;
    
  private:
    VectorArray vector_;
  }; // class Vector

}  // namespace la
}  // namespace sgbot

#endif  // _LA_VECTORBASE_H_
