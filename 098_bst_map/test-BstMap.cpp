#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> bMap;
  bMap.add(0, 0);
  bMap.add(-4, -4);
  bMap.add(-2, -2);
  bMap.add(-5, -5);
  bMap.add(3, 3);
  bMap.add(4, 4);
  bMap.add(2, 2);
  bMap.printBst();
  std::cout << "((((((((((((((((((((" << '\n';
  std::cout << "Now start to remove " << '\n';
  ;
  bMap.remove(-1);
  bMap.remove(0);
  bMap.remove(10);
  bMap.remove(3);
  bMap.remove(10111);
  bMap.printBst();
  return EXIT_SUCCESS;
}
