#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    data = temp;
    numElements = rhs.numElements;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert((index >= 0) && (index < numElements));
  const int & ans = data[index];
  return ans;
}
int & IntArray::operator[](int index) {
  assert((index >= 0) && (index < numElements));
  int & ans = data[index];
  return ans;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  //check the numelements
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < rhs.numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  bool notEqual = true;
  if (*this == rhs) {
    notEqual = false;
  }
  return notEqual;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    if (i != rhs.size() - 1) {
      s << rhs[i] << ",";
    }
    else {
      s << rhs[i];
    }
  }
  s << "}";
  return s;
}
