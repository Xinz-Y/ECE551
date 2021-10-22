#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns) {
  IntArray ** temp = new IntArray *[rhs.numRows];
  for (int i = 0; i < rhs.numRows; i++) {
    // every point open a space in heap and defualt constructor
    temp[i] = new IntArray;

    *(temp[i]) = IntArray(*(rhs.rows[i]));
  }
  rows = temp;
}

IntMatrix::~IntMatrix() {
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray;
      *(temp[i]) = IntArray(*(rhs.rows[i]));
    }
    delete[] rows;
    rows = temp;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert((index >= 0) && (index < numRows));
  return *(rows[index]);
}

IntArray & IntMatrix::operator[](int index) {
  assert((index >= 0) && (index < numRows));
  return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
    return false;
  }
  for (int r = 0; r < numRows; r++) {
    if (*(rows[r]) != *(rhs.rows[r])) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  IntMatrix ans(*this);
  for (int r = 0; r < numRows; r++) {
    for (int c = 0; c < numColumns; c++) {
      (*(ans.rows[r]))[c] = (*(rows[r]))[c] + (*(rhs.rows[r]))[c];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int r = 0; r < rhs.getRows(); r++) {
    if (r != rhs.getRows() - 1) {
      s << rhs[r];
      s << ",\n";
    }
    else {
      s << rhs[r];
    }
  }
  s << " ]";
  return s;
}
