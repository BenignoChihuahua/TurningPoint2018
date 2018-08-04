#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

#include "Matrix.hpp"

template <class T>
class Vector
{
  public:
    Vector();
    Vector(int elements);
    ~Vector();

    Vector operator+(const Vector &vec);
    Vector operator-(const Vector &vec);
    Vector operator*(const Matrix &mat);

    T dotProduct(Vector &vec);

    void push(int index);
    void pop(int index);
    void remove(int index);
    void add(T elem);
    void insert(T elem, int index);
    int length();

  private:
    typedef std::vector<T> Vec;
    Vec vector;
    int vecLength;
};

#endif
