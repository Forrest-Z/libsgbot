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

  MatrixBase& MatrixBase::operator +=(const double scalar)
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


  MatrixBase& MatrixBase::operator -=(const double scalar)
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


  MatrixBase& MatrixBase::operator *=(const double scalar)
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


  MatrixBase& MatrixBase::operator /=(const double scalar)
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


  MatrixBase MatrixBase::operator +(const double scalar) const
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


  MatrixBase MatrixBase::operator -(const double scalar) const
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


  MatrixBase MatrixBase::operator *(const double scalar) const
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


  MatrixBase MatrixBase::operator /(const double scalar) const
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
    MatrixBase left_mat(*this);

    assert(left_mat.getColumns() == matrix.getRows());

    MatrixBase result;

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
    double** matrix = result.getMatrix();

    double** temp = new double*[dimensions * 2];
    for(int i = 0; i < (dimensions * 2); i++)
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
        matrix[i][j] = temp[i][dimensions + j];
      }
    }

    for(int i = 0; i < dimensions; i++)
    {
      delete[] temp[i];
    }
    delete[] temp;

    return result;
  }


  MatrixBase MatrixBase::transpose() const
  {
    MatrixBase result(*this);
    result.resize(result.getColumns(), result.getRows());

    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) = matrix_[j][i];
      }
    }

    return result;
  }


  static double determinantRecuision(int dimensions, double** matrix, double** sub_matrix, double* pre_det)
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


  double MatrixBase::determinant() const
  {
    assert(rows_ == columns_);

    size_t dimensions = rows_;

    double det = 0.0f;

    double** temp = new double*[dimensions];
    for(int i = 0; i < dimensions; i++)
    {
      temp[i] = new double[dimensions];
    }

    double result = determinantRecuision(dimensions, matrix_, temp, &det);

    for(int i = 0; i < dimensions; i++)
    {
      delete[] temp[i];
    }
    delete[] temp;

    return result;
  }

}  // namespace la  
}  // namespace sgbot

#endif  // _USE_STD_ARITHMETIC_
