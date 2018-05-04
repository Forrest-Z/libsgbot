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
#include <linear-algebra/vectorbase.h>
#include <linear-algebra/matrix.h>
#include <vector>
#include <iomanip>

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
      : base_(I)
    {}

    // Define Destructor
    virtual ~Vector() {}

    // Copy constructor
    Vector(const Vector& other)
    {
      base_ = other.base_;
    }

    Vector(const VectorBase& base)
    {
      base_ = base;
    }

    Vector& operator =(const Vector<T, I>& other)
    {
      this->base_ = other.base_;
      return *this;
    }

    // Member functions
    virtual const size_t size() const
    {
      return base_.size();
    }

    virtual void resize(size_t items)
    {
      return base_.resize(items);
    }

    const VectorBase& content() const
    {
      return base_;
    }

    virtual void zero()
    {
      base_.zero();
    }

    // Copy operator
    virtual T& operator()(size_t index)
    {
      return base_(index);
    }
    
    virtual T operator()(size_t index) const
    {
      return static_cast<T>(base_(index));
    }

    // Vector monocular operators
    virtual Vector operator -() const
    {
      return Vector(-base_);
    }

    // Vector scale operators
    virtual Vector& operator *=(const T scalar)
    {
      float d = static_cast<T>(scalar);
      base_ *= d;
    }

    virtual Vector& operator /=(const T scalar)
    {
      float d = static_cast<T>(scalar);
      base_ /= d;
    }

    virtual Vector operator *(const T scalar) const
    {
      float d = static_cast<T>(scalar);
      return Vector(base_ * d);
    }

    virtual Vector operator /(const T scalar) const
    {
      float d = static_cast<T>(scalar);
      return Vector(base_ / d);
    }

    // Vector math operators
    virtual Vector& operator +=(const Vector& vector)
    {
      base_ += vector.base_;
    }

    virtual Vector& operator -=(const Vector& vector)
    {
      base_ -= vector.base_;
    }

    virtual Vector operator +(const Vector& vector) const
    {
      return Vector(base_ + vector.base_);
    }

    virtual Vector operator -(const Vector& vector) const
    {
      return Vector(base_ - vector.base_);
    }

    // Vector compare operators
    virtual bool operator ==(const Vector& vector) const
    {
      return (base_ == vector.base_);
    }

    virtual bool operator !=(const Vector& vector) const
    {
      return !(base_ == vector.base_);
    }

    // Vector other operators
    virtual T length() const
    {
      return static_cast<T>(base_.length());
    }

    virtual void normalize()
    {
      normalize();
    }

    virtual T dot(const Vector& vector) const
    {
      return static_cast<T>(base_.dot(vector.base_));
    }

    virtual Vector cross(const Vector& vector) const
    {
      return Vector(base_.cross(vector.base_));
    }
    
  protected:
    VectorBase base_;
  
  }; // class Vector

  template <typename T, size_t N>
  inline Vector<T, N> operator *(const Matrix<T, N, N>& lm, const Vector<T, N>& rv)
  {
    Matrix<T, N, 1> ref;

    for(int i = 0; i < rv.size(); i++)
    {
      ref(i, 0) = rv(i);
    }

    ref = lm * ref;

    Vector<T, N> result;

    for(int i = 0; i < ref.getRows(); i++)
    {
      result(i) = ref(i, 0);
    }

    return result;
  }

  template <typename T, size_t I>
  inline std::ostream& operator <<(std::ostream& output, const Vector<T, I>& vector)
  {
    output << std::endl;
    output << "[";
    for(int i = 0; i < vector.size(); i++)
    {
      output << std::fixed << std::setprecision(2) << vector(i) << ", ";
    }
    output << "]" << std::endl;
    return output;
  }

}  // namespace la
}  // namespace sgbot

#endif  // _LA_VECTOR_H_
