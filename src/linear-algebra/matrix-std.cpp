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

  // Guass-Jordan method
  template <typename T, size_t R, size_t C>
  Matrix<T, R, C> Matrix<T, R, C>::inverse() const
  {
    Matrix<T, R, C> result(*this);

    assert(result.getRows() == result.getColumns());

    size_t dimensions = result.getRows();
    T** matrix = result.getMatrix();

    double** temp = new double*[dimensions];
    for(int i = 0; i < dimensions; i++)
    {
      temp[i] = new double[dimensions * 2];
    }

    // Copy input matrix and construct a augmented matrix
    for(int i = 0; i < dimensions; i++)
    {
      for(int j = 0; j < (dimensions * 2); j++)
      {
        if(j < dimensions)
        {
          temp[i][j] = static_cast<double>(matrix[i][j]);
        }
        else if(j == (i + dimensions))
        {
          temp[i][j] = 1.0f;
        }
        else
        {
          temp[i][j] = 0.0f;
        }
      }
    }

    // Exchange two rows
    for(int i = (dimensions - 1); i > 0; i--)
    {
      if(temp[i - 1][0] < temp[i][0])
      {
        for(int j = 0; j < (dimensions * 2); j++)
        {
          double element = temp[i][j];
          temp[i][j] = temp[i - 1][j];
          temp[i - 1][j] = element;
        }
      }
    }

    // Reducing to diagonal matrix
    for(int i = 0; i < dimensions; i++)
    {
      for(int j = 0; j < (dimensions * 2); j++)
      {
        if(j != 0)
        {
          double div = temp[j][i] / temp[i][i];
          for(int k = 0; k < (dimensions * 2); k++)
          {
            temp[j][k] -= temp[i][k] * div;
          }
        }
      }
    }

    // Reducing to unit matrix
    for(int i = 0; i < dimensions; i++)
    {
      double element = temp[i][i];
      for(int j = 0; j < (dimensions * 2); j++)
      {
        temp[i][j] /= element;
      }
    }

    // Copy right part back to input matrix
    for(int i = 0; i < dimensions; i++)
    {
      for(int j = 0; j < dimensions; j++)
      {
        matrix[i][j] = static_cast<T>(temp[i][dimensions + j]);
      }
    }

    for(int i = 0; i < dimensions; i++)
    {
      delete[] temp[i];
    }
    delete[] temp;

    return result;
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
