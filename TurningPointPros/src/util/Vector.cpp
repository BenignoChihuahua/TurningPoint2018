#include <iostream>
#include "Vector.hpp"

Vector::Vector(){
  for(int i = 0; i < 3; ++i)
  {
    vector[i] = 0;
  }
}

Vector::Vector(int elements){
  for(int i = 0; i < elements; ++i)
  {
    vector[i] = 0;
  }
}

Vector::~Vector(){

}

Vector Vector::operator+(const Vector &vec){
  int index = 0;
  for(T elem : vec)
  {
    vector[index] += elem;
    index++;
  }
}

Vector Vector::operator-(const Vector &vec){
  int index = 0;
  for(T elem : vec)
  {
    vector[index] -= elem;
    index++;
  }
}
Vector Vector::operator*(const Matrix &mat){

}

T dotProduct(Vector &vec);

void push(int index){

}

void pop(int index){

}

void remove(int index){

}

void add(T elem, int index){

}

void insert(T elem, int index){

}

int length(){

}
