/* Created linear-algebra/vector.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _LA_VECTOR_H_
#define _LA_VECTOR_H_

#include <common/exception.h>

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
  
  template <typename T, size_t I>
  class Vector {
  public:
    // Define Constructors
    Vector()
      :items_(I)
    {}

    // Define Destructor
    virtual ~Vector() {}

    // Copy constructor
    Vector(const Vector& vector) {}

    // Member functions
    
    size_t getItemCount() {
      return items_;
    }

    // Copy operator
    virtual T& operator()(size_t index) {

    }
    
    virtual T operator()(size_t index) const {

    }

    // Vector monocular operators
    virtual Vector operator -() const;

    // Vector scale operators
    virtual Vector<T, I>& operator *=(const T scalar);
    virtual Vector<T, I>& operator /=(const T scalar);

    virtual Vector operator *(const T scalar) const;
    virtual Vector operator /(const T scalar) const;

    // Vector math operators
    virtual Vector<T, I>& operator +=(const Vector& vector);
    virtual Vector<T, I>& operator -=(const Vector& vector);

    virtual Vector operator +(const Vector& vector) const;
    virtual Vector operator -(const Vector& vector) const;

    // Vector compare operators
    virtual bool operator ==(const Vector& vector) const;
    virtual bool operator !=(const Vector& vector) const;

    // Vector other operators
    virtual T length() const;
    virtual T normalize() const;
    virtual T dot() const;
    virtual Vector cross(const Vector& vector) const;
    
  private:
    T vector_[I];
    size_t items_;
  
  }; // class Vector

}  // namespace la
}  // namespace sgbot

#endif  // _LA_VECTOR_H_
