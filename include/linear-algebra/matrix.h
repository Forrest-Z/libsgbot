/* Created linear-algebra/matrix.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _LA_MATRIX_H_
#define _LA_MATRIX_H_

#include <assert.h>
#include <vector>
#include <common/exception.h>
#include <linear-algebra/matrixbase.h>

namespace sgbot {
namespace la {
  /*
  class MatrixException: public sgbot::Exception {
  private:
    
  public:
    MatrixException(std::string ex_what)
      : ex_what_(ex_what) {}
    virtual ~MatrixException() throw() {}
  };
  */
  template <typename T, size_t R, size_t C>
  class Matrix {
  public:
    // Define Constructors
    Matrix()
      : base_(MatrixBase(R, C))
    {}

    // Define Destructor
    virtual ~Matrix()
    {}

    // Member functions
    virtual const size_t getRows() const
    {
      return base_.getRows();
    }
    
    virtual const size_t getColumns() const
    {
      return base_.getColumns();
    }

    virtual void resize(size_t rows, size_t columns)
    {
      base_.resize(rows, columns);
    }

    const MatrixBase& content() const
    {
      return base_;
    }

    // Copy constructor
    Matrix(const Matrix& other)
    {
      base_ = other.base_;
    }

    Matrix(const MatrixBase& base)
    {
      base_ = base;
    }

    Matrix& operator =(const Matrix<T, R, C>& other)
    {
      this->base_ = other.base_;
      return *this;
    }

    // Copy operator
    virtual T& operator()(size_t row, size_t column)
    {
      return base_(row, column);
    }
    
    virtual const T operator()(size_t row, size_t column) const
    {
      return static_cast<T>(base_(row, column));;
    }

    // Matrix scalar operators
    virtual Matrix& operator +=(const T scalar)
    {
      float d = static_cast<T>(scalar);
      base_ += d;
    }

    virtual Matrix& operator -=(const T scalar)
    {
      float d = static_cast<T>(scalar);
      base_ -= d;
    }

    virtual Matrix& operator *=(const T scalar)
    {
      float d = static_cast<T>(scalar);
      base_ *= d;
    }

    virtual Matrix& operator /=(const T scalar)
    {
      float d = static_cast<T>(scalar);
      base_ /= d;
    }

    virtual Matrix operator +(const T scalar) const
    {
      float d = static_cast<T>(scalar);
      return Matrix(base_ + d);
    }

    virtual Matrix operator -(const T scalar) const
    {
      float d = static_cast<T>(scalar);
      return Matrix(base_ - d);
    }

    virtual Matrix operator *(const T scalar) const
    {
      float d = static_cast<T>(scalar);
      return Matrix(base_ * d);
    }

    virtual Matrix operator /(const T scalar) const
    {
      float d = static_cast<T>(scalar);
      return Matrix(base_ / d);
    }

    // Matrix math operators
    virtual Matrix& operator +=(const Matrix<T, R, C>& matrix)
    {
      base_ += matrix.base_;
    }

    virtual Matrix& operator -=(const Matrix<T, R, C>& matrix)
    {
      base_ += matrix.base_;
    }

    virtual Matrix operator +(const Matrix<T, R, C>& matrix) const
    {
      return Matrix(base_ + matrix.base_);
    }

    virtual Matrix operator -(const Matrix<T, R, C>& matrix) const
    {
      return Matrix(base_ - matrix.base_);
    }

    virtual bool operator ==(const Matrix<T, R, C>& matrix) const
    {
      return (base_ == matrix.base_);
    }

    // Matrix transform
    virtual Matrix inverse() const
    {
      return Matrix(base_.inverse());
    }

    virtual Matrix<T, C, R> transpose() const
    {
      Matrix<T, C, R> result(base_.transpose());
      return result;
    }

    virtual T determinant() const
    {
      float result;
      result = base_.determinant();
      return static_cast<T>(result);
    }

    // Other Matrix operations
    virtual void indentity()
    {
      base_.indentity();
    }

    virtual T sum() const
    {
      return static_cast<T>(base_.sum());
    }

    virtual void zero()
    {
      base_.zero();
    }

  protected:
    MatrixBase base_;
  }; // class Matrix

  template <typename T, size_t R0, size_t C0, size_t R1, size_t C1>
  inline Matrix<T, R0, C1> operator *(const Matrix<T, R0, C0>& lm, const Matrix<T, R1, C1>& rm)
  {
    return Matrix<T, R0, C1>(lm.content() * rm.content());
  }


  template <typename T, size_t R, size_t C>
  inline std::ostream& operator <<(std::ostream& output, const Matrix<T, R, C>& matrix)
  {
    output << std::endl;
    output << "[" << std::endl;

    for(int i = 0; i < matrix.getRows(); i++)
    {
      for(int j = 0; j < matrix.getColumns(); j++)
      {
        output << " " << matrix(i, j);
      }
      output << " " << std::endl;
    }

    output << "]" << std::endl;

    return output;
  }

}  // namespace la
}  // namespace sgbot

#endif  // _LA_MATRIX_H_
