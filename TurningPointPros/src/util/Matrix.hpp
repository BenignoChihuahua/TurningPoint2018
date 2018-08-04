#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <vector>
#include <stdexcept>

#include "Vector.hpp"

class Matrix {

public:

  /**
   * m - rows
   * n - cols
   */
  Matrix(int m, int n);

  /**
  * Creates a null matrix.
  */
  Matrix();

  Matrix operator*(const Matrix &mat)
  {
    if(!(this->rows() != mat.cols()))
      throw std::runtime_error("Matrix is not of the same dimension!, Cannot Multiply");

    int n = this->rows();
    for(int i = 0; i < n; i++)
    {

    }
  }

  void getVector(int index);
  void addVector(int index);
  void removeVector(int index);
  void insertVector(int index);
  void insert(int row, int col);

  void transpose();
  void inverse();
  void adjoint();

  int rows() const;
  int cols() const;

private:
  typedef std::vector<Vector> Mat;
  int numRows;
  int numCols;

};


#endif
