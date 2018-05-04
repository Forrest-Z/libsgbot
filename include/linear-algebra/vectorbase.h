/* Created linear-algebra/vectorbase.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _LA_VECTORBASE_H_
#define _LA_VECTORBASE_H_

#include <assert.h>
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
  
  typedef std::vector<float> VectorArray;

  class VectorBase {
  public:
    // Define Constructors
    VectorBase()
    {}

    VectorBase(size_t items)
    {
      resize(items);
    }

    // Define Destructor
    virtual ~VectorBase() {}

    // Copy constructor
    VectorBase(const VectorBase& other)
    {
      this->resize(other.size());
      for(int i = 0; i < this->size(); i++)
      {
        items_[i] = other(i);
      }
    }

    VectorBase operator =(const VectorBase& other) const
    {
      VectorBase vec;

      vec.resize(other.size());

      for(int i = 0; i < this->size(); i++)
      {
        vec(i) = other(i);
      }

      return vec;
    }

    VectorBase& operator =(const VectorBase& other)
    {
      if(this == &other)
      {
        return *this;
      }

      this->resize(other.size());

      for(int i = 0; i < this->size(); i++)
      {
        items_[i] = other(i);
      }

      return *this;
    }

    // Member functions
    virtual const size_t size() const
    {
      return items_.size();
    }

    virtual void resize(size_t items)
    {
      items_.resize(items);
    }

    virtual void zero()
    {
      for(int i = 0; i < this->size(); i++)
      {
        items_[i] = 0.0f;
      }
    }

    // Copy operator
    virtual float& operator()(size_t index)
    {
      assert(index < size());

      return items_[index];
    }
    
    virtual const float operator()(size_t index) const
    {
      assert(index < size());

      return items_[index];
    }

    // Vector monocular operators
    virtual VectorBase operator -() const;

    // Vector scale operators
    virtual VectorBase& operator *=(const float scalar);
    virtual VectorBase& operator /=(const float scalar);

    virtual VectorBase operator *(const float scalar) const;
    virtual VectorBase operator /(const float scalar) const;

    // Vector math operators
    virtual VectorBase& operator +=(const VectorBase& vector);
    virtual VectorBase& operator -=(const VectorBase& vector);

    virtual VectorBase operator +(const VectorBase& vector) const;
    virtual VectorBase operator -(const VectorBase& vector) const;

    // Vector compare operators
    virtual bool operator ==(const VectorBase& vector) const;

    // Vector other operators
    virtual float length() const;
    virtual void normalize();
    virtual float dot(const VectorBase& vector) const;
    virtual VectorBase cross(const VectorBase& vector) const;
    
  private:
    VectorArray items_;
  }; // class VectorBase

}  // namespace la
}  // namespace sgbot

#endif  // _LA_VECTORBASE_H_
