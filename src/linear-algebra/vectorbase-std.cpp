/* Created linear-algebra/vectorbase-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <linear-algebra/vectorbase.h>
#include <std-math/math.h>

namespace sgbot {
namespace la {

  VectorBase VectorBase::operator -() const
  {
    VectorBase v(*this);
    for(int i = 0; i < size(); i++)
    {
      v(i) = -v(i);
    }
    return v;
  }

  VectorBase& VectorBase::operator *=(const float scalar)
  {
    VectorBase& v = *this;
    for(int i = 0; i < size(); i++)
    {
      v(i) *= scalar;
    }
    return v;
  }

  VectorBase& VectorBase::operator /=(const float scalar)
  {
    VectorBase& v = *this;
    for(int i = 0; i < size(); i++)
    {
      v(i) /= scalar;
    }
    return v;
  }

  VectorBase VectorBase::operator *(const float scalar) const
  {
    VectorBase v(*this);
    for(int i = 0; i < size(); i++)
    {
      v(i) *= scalar;
    }
    return v;
  }

  VectorBase VectorBase::operator /(const float scalar) const
  {
    VectorBase v(*this);
    for(int i = 0; i < size(); i++)
    {
      v(i) /= scalar;
    }
    return v;
  }

  VectorBase& VectorBase::operator +=(const VectorBase& vector)
  {
    VectorBase& v = *this;
    assert(v.size() == vector.size());

    for(int i = 0; i < size(); i++)
    {
      v(i) += vector(i);
    }

    return v;
  }

  VectorBase& VectorBase::operator -=(const VectorBase& vector)
  {
    VectorBase& v = *this;
    assert(v.size() == vector.size());

    for(int i = 0; i < size(); i++)
    {
      v(i) -= vector(i);
    }

    return v;
  }

  VectorBase VectorBase::operator +(const VectorBase& vector) const
  {
    VectorBase v(*this);
    assert(v.size() == vector.size());

    for(int i = 0; i < size(); i++)
    {
      v(i) += vector(i);
    }

    return v;
  }

  VectorBase VectorBase::operator -(const VectorBase& vector) const
  {
    VectorBase v(*this);
    assert(v.size() == vector.size());

    for(int i = 0; i < size(); i++)
    {
      v(i) -= vector(i);
    }

    return v;
  }

  bool VectorBase::operator ==(const VectorBase& vector) const
  {
    if(this->size() != vector.size())
    {
      return false;
    }

    for(int i = 0; i < size(); i++)
    {
      if(items_[i] != vector(i))
      {
        return false;
      }
    }

    return true;
  }

  float VectorBase::length() const
  {
    return sgbot::math::sqrt(dot(*this));
  }

  void VectorBase::normalize()
  {
    float len = length();

    if(len < 1e-6)
    {
      len = 1;
    }

    len = 1 / len;

    for(int i = 0; i < this->size(); i++)
    {
      items_[i] *= len;
    }
  }

  float VectorBase::dot(const VectorBase& vector) const
  {
    assert(this->size() == vector.size());

    float result = 0.0f;

    for(int i = 0; i < this->size(); i++)
    {
      result += (items_[i] * vector(i));
    }

    return result;
  }

  VectorBase VectorBase::cross(const VectorBase& vector) const
  {
    assert(this->size() == 3);
    assert(this->size() == vector.size());

    VectorBase v(3);

    v(0) = items_[1] * vector(2) - items_[2] * vector(1);
    v(1) = items_[2] * vector(0) - items_[0] * vector(2);
    v(2) = items_[0] * vector(1) - items_[1] * vector(0);

    return v;
  }

}  // namespace la  
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
