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
      : rows_(R), columns_(C)
    {
      matrix_ = new T*[rows_];
      for(int i = 0; i < rows_; i++)
      {
        matrix_[i] = new T[columns_];
      }
    }

    // Define Destructor
    virtual ~Matrix()
    {
      for(int i = 0; i < rows_; i++)
      {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      matrix_ = NULL;
    }

    // Copy constructor
    Matrix(const Matrix& other)
    {
      resize(other.getRows(), other.getColumns());

      for(int i = 0; i < rows_; i++)
        for(int j = 0; j < columns_; j++)
          matrix_[i][j] = other(i, j);
    }

    Matrix& operator =(const Matrix& other) const
    {
      Matrix matrix(other);
      return other;
    }

    // Member functions
    size_t getRows()
    {
      return rows_;
    }
    
    size_t getColumns()
    {
      return columns_;
    }

    void resize(size_t rows, size_t columns)
    {
      for(int i = 0; i < rows_; i++)
      {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      matrix_ = NULL;

      matrix_ = new T*[rows_];
      for(int i = 0; i < rows_; i++)
      {
        matrix_[i] = new T[columns_];
      }

      rows_ = rows;
      columns_ = columns;
    }

    // Copy operator
    virtual T& operator()(size_t row, size_t column)
    {
      assert(row < rows_);
      assert(column < columns_);

      return matrix_[row][column];
    }
    
    virtual T operator()(size_t row, size_t column) const
    {
      assert(row < rows_);
      assert(column < columns_);

      return matrix_[row][column];
    }

    // Matrix scalar operators
    virtual Matrix<T, R, C>& operator +=(const T scalar);
    virtual Matrix<T, R, C>& operator -=(const T scalar);
    virtual Matrix<T, R, C>& operator *=(const T scalar);
    virtual Matrix<T, R, C>& operator /=(const T scalar);

    virtual Matrix operator +(const T scalar) const;
    virtual Matrix operator -(const T scalar) const;
    virtual Matrix operator *(const T scalar) const;
    virtual Matrix operator /(const T scalar) const;

    // Matrix math operators
    virtual Matrix<T, R, C>& operator +=(const Matrix& matrix);
    virtual Matrix<T, R, C>& operator -=(const Matrix& matrix);

    virtual Matrix operator +(const Matrix& matrix) const;
    virtual Matrix operator -(const Matrix& matrix) const;
    virtual Matrix operator *(const Matrix& matrix) const;
    virtual bool operator ==(const Matrix& matrix) const;

    // Matrix transform
    virtual Matrix inverse() const;
    virtual Matrix transpose() const;
    virtual T determinant() const;

    // Other Matrix operations
    void indentity()
    {
      assert(rows_ == columns_);

      for(int i = 0; i < rows_; i++)
      {
        matrix_[i][i] = static_cast<T>(1.0f);
      }
    }
  
  protected:
    T** getMatrix() const
    {
      return matrix_;
    }

  private:
    T** matrix_;
    size_t rows_, columns_;
  
  }; // class Matrix

}  // namespace la
}  // namespace sgbot

#endif  // _LA_MATRIX_H_
