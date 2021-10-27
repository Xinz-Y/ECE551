#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs);
  ~Matrix();
  Matrix<T> & operator=(const Matrix<T> & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
  // friend std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);
  template<typename X>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<X> & rhs);
};

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows(0) {
}
template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c), rows(r) {
  typename std::vector<std::vector<T> >::iterator it = rows.begin();
  while (it != rows.end()) {
    std::vector<T> vect(c);
    *it = vect;
    ++it;
  }
}
template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(rhs.rows) {
}

template<typename T>
Matrix<T>::~Matrix() {
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}
template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}
template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(0 <= index && (size_t)index < rows.size());
  return rows[index];
}
template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  if (rows != rhs.rows) {
    return false;
  }
  return true;
}
/*
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> ans(rhs.numRows, rhs.numColumns);
  for (int i = 0; i < rhs.numRows; i++) {
    for (int j = 0; j < rhs.numColumns; j++) {
      ans[i][j] = this[i][j] + rhs[i][j];
    }
  }
  return ans;
}
*/

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> ans(numRows, numColumns);
  typename std::vector<std::vector<T> >::iterator z = ans.rows.begin();
  typename std::vector<std::vector<T> >::const_iterator x = rows.begin();
  typename std::vector<std::vector<T> >::const_iterator y = rhs.rows.begin();
  while (z != ans.rows.end()) {
    typename std::vector<T>::iterator zc = z->begin();
    typename std::vector<T>::const_iterator xc = x->begin(), yc = y->begin();
    while (zc != z->end()) {
      *zc++ = *xc++ + *yc++;
    }
    ++z;
    ++x;
    ++y;
  }
  return ans;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[";
  for (int i = 0; i < rhs.numRows; i++) {
    s << "{";
    for (int j = 0; j < rhs.numColumns; j++) {
      if (j == 0) {
        s << (rhs[i])[j];
      }
      else {
        s << ",";
        s << (rhs[i])[j];
      }
    }
    if (i == rhs.numRows - 1) {
      s << "}";
      continue;
    }
    s << "}" << std::endl;
  }
  s << "]";
  return s;
}

#endif
