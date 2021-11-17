#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> bMap;
  bMap.add(11, 11);
  bMap.printBst();
  return EXIT_SUCCESS;
}
