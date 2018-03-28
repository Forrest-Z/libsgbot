/* Created linear-algebra/matrix-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <linear-algebra/matrix.h>

namespace sgbot {
namespace la {
  template <typename T, size_t R, size_t C>
  Matrix<T, R, C>& Matrix<T, R, C>::operator +=(const T scalar)
  {
    Matrix<T, R, C>& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) += scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C>& Matrix<T, R, C>::operator -=(const T scalar)
  {
    Matrix<T, R, C>& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) -= scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C>& Matrix<T, R, C>::operator *=(const T scalar)
  {
    Matrix<T, R, C>& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) *= scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C>& Matrix<T, R, C>::operator /=(const T scalar)
  {
    Matrix<T, R, C>& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) /= scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::operator +(const T scalar) const
  {
    Matrix<T, R, C> matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) += scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::operator -(const T scalar) const
  {
    Matrix<T, R, C> matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) -= scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::operator *(const T scalar) const
  {
    Matrix<T, R, C> matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) *= scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::operator /(const T scalar) const
  {
    Matrix<T, R, C> matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) /= scalar;
      }
    }

    return matrix;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C>& Matrix<T, R, C>::operator +=(const Matrix& matrix)
  {
    Matrix<T, R, C>& result = *this;

    assert(result.getRows() == matrix.getRows());
    assert(result.getColumns() == matrix.getColumns());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) += matrix(i, j);
      }
    }

    return result;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C>& Matrix<T, R, C>::operator -=(const Matrix& matrix)
  {
    Matrix<T, R, C>& result = *this;

    assert(result.getRows() == matrix.getRows());
    assert(result.getColumns() == matrix.getColumns());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) -= matrix(i, j);
      }
    }

    return result;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::operator +(const Matrix& matrix) const
  {
    Matrix<T, R, C> result(*this);

    assert(result.getRows() == matrix.getRows());
    assert(result.getColumns() == matrix.getColumns());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) += matrix(i, j);
      }
    }

    return result;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::operator -(const Matrix& matrix) const
  {
    Matrix<T, R, C> result(*this);

    assert(result.getRows() == matrix.getRows());
    assert(result.getColumns() == matrix.getColumns());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) -= matrix(i, j);
      }
    }

    return result;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::operator *(const Matrix& matrix) const
  {
    Matrix<T, R, C>& left_mat =*this;

    assert(left_mat.getColumns() == matrix.getRows());

    Matrix<T, R, C> result;

    result.resize(left_mat.getRows(), matrix.getColumns());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) = 0;
        for(int k = 0; k < left_mat.getColumns(); k++)
        {
          result(i, j) += left_mat(i, k) * matrix(k, j);
        }
      }
    }

    return result;
  }

  template <typename T, size_t R, size_t C>
  bool Matrix<T, R, C>::operator ==(const Matrix& matrix) const
  {
    Matrix<T, R, C> left_mat(*this);

    if(left_mat.getRows() != matrix.getRows())
    {
      return false;
    }

    if(left_mat.getColumns() != matrix.getColumns())
    {
      return false;
    }

    for(int i = 0; i < left_mat.getRows(); i++)
    {
      for(int j = 0; j < left_mat.getColumns(); j++)
      {
        if(left_mat(i, j) != matrix(i, j))
        {
          return false;
        }
      }
    }

    return true;
  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::inverse() const
  {

  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::transpose() const
  {

  }

  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::determinant() const
  {

  }

}  // namespace la  
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
