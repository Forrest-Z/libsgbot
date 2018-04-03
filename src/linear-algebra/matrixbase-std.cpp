/* Created linear-algebra/matrixbase-std.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_STD_ARITHMETIC_

#include <linear-algebra/matrixbase.h>
#include <std-math/math.h>

namespace sgbot {
namespace la {

  MatrixBase& MatrixBase::operator +=(const float scalar)
  {
    MatrixBase& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) += scalar;
      }
    }

    return matrix;
  }


  MatrixBase& MatrixBase::operator -=(const float scalar)
  {
    MatrixBase& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) -= scalar;
      }
    }

    return matrix;
  }


  MatrixBase& MatrixBase::operator *=(const float scalar)
  {
    MatrixBase& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) *= scalar;
      }
    }

    return matrix;
  }


  MatrixBase& MatrixBase::operator /=(const float scalar)
  {
    MatrixBase& matrix = *this;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) /= scalar;
      }
    }

    return matrix;
  }


  MatrixBase MatrixBase::operator +(const float scalar) const
  {
    MatrixBase matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) += scalar;
      }
    }

    return matrix;
  }


  MatrixBase MatrixBase::operator -(const float scalar) const
  {
    MatrixBase matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) -= scalar;
      }
    }

    return matrix;
  }


  MatrixBase MatrixBase::operator *(const float scalar) const
  {
    MatrixBase matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) *= scalar;
      }
    }

    return matrix;
  }


  MatrixBase MatrixBase::operator /(const float scalar) const
  {
    MatrixBase matrix(*this);

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        matrix(i, j) /= scalar;
      }
    }

    return matrix;
  }


  MatrixBase& MatrixBase::operator +=(const MatrixBase& matrix)
  {
    MatrixBase& result = *this;

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


  MatrixBase& MatrixBase::operator -=(const MatrixBase& matrix)
  {
    MatrixBase& result = *this;

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


  MatrixBase MatrixBase::operator +(const MatrixBase& matrix) const
  {
    MatrixBase result(*this);

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


  MatrixBase MatrixBase::operator -(const MatrixBase& matrix) const
  {
    MatrixBase result(*this);

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


  MatrixBase MatrixBase::operator *(const MatrixBase& matrix) const
  {
    assert(this->getColumns() == matrix.getRows());

    MatrixBase result(this->getRows(), matrix.getColumns());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) = 0;
        for(int k = 0; k < this->getColumns(); k++)
        {
          result(i, j) += matrix_[i][k] * matrix(k, j);
        }
      }
    }

    return result;
  }


  bool MatrixBase::operator ==(const MatrixBase& matrix) const
  {
    MatrixBase left_mat(*this);

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

  MatrixBase MatrixBase::inverse() const
  {
    MatrixBase result(*this);

    assert(result.getRows() == result.getColumns());

    size_t dimensions = result.getRows();
    MatrixArray& matrix = result.getMatrix();

    MatrixArray temp;
    temp.resize(dimensions * 2);
    for(int i = 0; i < (dimensions * 2); i++)
    {
      temp[i].resize(dimensions * 2);
    }

    // Copy input matrix and construct a augmented matrix
    for(int i = 0; i < dimensions; i++)
    {
      for(int j = 0; j < (dimensions * 2); j++)
      {
        if(j < dimensions)
        {
          temp[i][j] = matrix[i][j];
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
          float element = temp[i][j];
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
        if(j != i)
        {
          float div = temp[j][i] / temp[i][i];
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
      float element = temp[i][i];
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
        matrix[i][j] = temp[i][dimensions + j];
      }
    }

    return result;
  }


  MatrixBase MatrixBase::transpose() const
  {
    assert(this->getRows() > 0);
    assert(this->getColumns() > 0);

    MatrixBase result(this->getColumns(), this->getRows());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) = matrix_[j][i];
      }
    }

    return result;
  }

  static float determinantRecuision(int dimensions, const MatrixArray& matrix, MatrixArray& sub_matrix, float* pre_det)
  {
    if(dimensions == 2)
    {
      return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    }
    else
    {
      for(int i = 0; i < dimensions; i++)
      {
        int sub_row = 0;
        for(int j = 1; j < dimensions; j++)
        {
          int sub_col = 0;
          for(int k = 0; k < dimensions; k++)
          {
            if(k == i)
            {
              continue;
            }
            sub_matrix[sub_row][sub_col] = matrix[j][k];
            sub_col++;
          }
          sub_row++;
        }
        *pre_det += (sgbot::math::pow(-1, i) * matrix[0][i] * determinantRecuision((dimensions - 1), sub_matrix, sub_matrix, pre_det));
      }
    }
    return *pre_det;
  }


  float MatrixBase::determinant() const
  {
    assert(getRows() == getColumns());

    size_t dimensions = getRows();

    float det = 0.0f;

    MatrixArray temp;
    temp.resize(dimensions);
    for(int i = 0; i < dimensions; i++)
    {
      temp[i].resize(dimensions);
    }

    float result = determinantRecuision(dimensions, matrix_, temp, &det);

    return result;
  }

}  // namespace la  
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
