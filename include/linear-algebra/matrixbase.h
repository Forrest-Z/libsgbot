/* Created linear-algebra/matrixbase.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _LA_MATRIXBASE_H_
#define _LA_MATRIXBASE_H_

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
  
  class MatrixBase {
  public:
    // Define Constructors
    MatrixBase()
      : rows_(0), columns_(0), matrix_(NULL)
    {}

    MatrixBase(size_t rows, size_t columns)
      : rows_(rows), columns_(columns)
    {
      matrix_ = new double*[rows_];
      for(int i = 0; i < rows_; i++)
      {
        matrix_[i] = new double[columns_];
      }
    }

    // Define Destructor
    virtual ~MatrixBase()
    {
      for(int i = 0; i < rows_; i++)
      {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      matrix_ = NULL;
    }

    // Member functions
    virtual const size_t getRows() const
    {
      return rows_;
    }
    
    virtual const size_t getColumns() const
    {
      return columns_;
    }

    virtual void resize(size_t rows, size_t columns)
    {
      for(int i = 0; i < rows_; i++)
      {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      matrix_ = NULL;

      matrix_ = new double*[rows_];
      for(int i = 0; i < rows_; i++)
      {
        matrix_[i] = new double[columns_];
      }

      rows_ = rows;
      columns_ = columns;
    }

    // Copy constructor
    MatrixBase(const MatrixBase& other)
    {
      this->resize(other.getRows(), other.getColumns());

      for(int i = 0; i < rows_; i++)
        for(int j = 0; j < columns_; j++)
          matrix_[i][j] = other(i, j);
    }

    MatrixBase operator =(const MatrixBase& other) const
    {
      MatrixBase matrix;

      matrix.resize(other.getRows(), other.getColumns());

      for(int i = 0; i < matrix.getRows(); i++)
        for(int j = 0; j < matrix.getColumns(); j++)
          matrix(i, j) = other(i, j);

      return matrix;
    }

    MatrixBase& operator =(const MatrixBase& other)
    {
      *this = other;

      return *this;
    }

    // Copy operator
    virtual double& operator()(size_t row, size_t column)
    {
      assert(row < rows_);
      assert(column < columns_);

      return matrix_[row][column];
    }
    
    virtual const double operator()(size_t row, size_t column) const
    {
      assert(row < rows_);
      assert(column < columns_);

      return matrix_[row][column];
    }

    // Matrix scalar operators
    virtual MatrixBase& operator +=(const double scalar);
    virtual MatrixBase& operator -=(const double scalar);
    virtual MatrixBase& operator *=(const double scalar);
    virtual MatrixBase& operator /=(const double scalar);

    virtual MatrixBase operator +(const double scalar) const;
    virtual MatrixBase operator -(const double scalar) const;
    virtual MatrixBase operator *(const double scalar) const;
    virtual MatrixBase operator /(const double scalar) const;

    // Matrix math operators
    virtual MatrixBase& operator +=(const MatrixBase& matrix);
    virtual MatrixBase& operator -=(const MatrixBase& matrix);

    virtual MatrixBase operator +(const MatrixBase& matrix) const;
    virtual MatrixBase operator -(const MatrixBase& matrix) const;
    virtual MatrixBase operator *(const MatrixBase& matrix) const;
    virtual bool operator ==(const MatrixBase& matrix) const;

    // Matrix transform
    virtual MatrixBase inverse() const;
    virtual MatrixBase transpose() const;
    virtual double determinant() const;

    // Other Matrix operations
    virtual void indentity()
    {
      assert(rows_ == columns_);

      for(int i = 0; i < rows_; i++)
      {
        matrix_[i][i] = 1.0f;
      }
    }
  
  protected:
    double** getMatrix() const
    {
      return matrix_;
    }

  private:
    double** matrix_;
    size_t rows_, columns_;
  
  }; // class MatrixBase

}  // namespace la
}  // namespace sgbot

#endif  // _LA_MATRIXBASE_H_
