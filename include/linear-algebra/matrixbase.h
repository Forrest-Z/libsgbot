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
  
  typedef std::vector<std::vector<float> > MatrixArray;

  class MatrixBase {
  public:
    // Define Constructors
    MatrixBase()
    {}

    MatrixBase(size_t rows, size_t columns)
    {
      resize(rows, columns);
      zero();
    }

    // Define Destructor
    virtual ~MatrixBase()
    {}

    // Member functions
    virtual void zero()
    {
      for(int i = 0; i < getRows(); i++)
        for(int j = 0; j < getColumns(); j++)
          matrix_[i][j] = 0.0f;
    }

    virtual const size_t getRows() const
    {
      return matrix_.size();
    }
    
    virtual const size_t getColumns() const
    {
      return matrix_[0].size();
    }

    virtual void resize(size_t rows, size_t columns)
    {
      matrix_.resize(rows);
      for(int i = 0; i < rows; i++)
      {
        matrix_[i].resize(columns);
      }
    }

    // Copy constructor
    MatrixBase(const MatrixBase& other)
    {
      this->resize(other.getRows(), other.getColumns());

      for(int i = 0; i < getRows(); i++)
        for(int j = 0; j < getColumns(); j++)
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
      if(this == &other)
      {
        return *this;
      }

      this->resize(other.getRows(), other.getColumns());

      for(int i = 0; i < getRows(); i++)
        for(int j = 0; j < getColumns(); j++)
          matrix_[i][j] = other(i, j);

      return *this;
    }

    // Copy operator
    virtual float& operator()(size_t row, size_t column)
    {
      assert(row < getRows());
      assert(column < getColumns());

      return matrix_[row][column];
    }
    
    virtual const float operator()(size_t row, size_t column) const
    {
      assert(row < getRows());
      assert(column < getColumns());

      return matrix_[row][column];
    }

    // Matrix scalar operators
    virtual MatrixBase& operator +=(const float scalar);
    virtual MatrixBase& operator -=(const float scalar);
    virtual MatrixBase& operator *=(const float scalar);
    virtual MatrixBase& operator /=(const float scalar);

    virtual MatrixBase operator +(const float scalar) const;
    virtual MatrixBase operator -(const float scalar) const;
    virtual MatrixBase operator *(const float scalar) const;
    virtual MatrixBase operator /(const float scalar) const;

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
    virtual float determinant() const;

    // Other Matrix operations
    virtual void indentity()
    {
      assert(getRows() == getColumns());

      for(int i = 0; i < getRows(); i++)
      {
        matrix_[i][i] = 1.0f;
      }
    }
  
  protected:
    MatrixArray& getMatrix()
    {
      return matrix_;
    }

  private:
    MatrixArray matrix_;
  }; // class MatrixBase

}  // namespace la
}  // namespace sgbot

#endif  // _LA_MATRIXBASE_H_
