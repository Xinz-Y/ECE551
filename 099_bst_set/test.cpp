#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> bst;
  bst.add(1);
  bst.add(2);
  bst.add(3);
  bst.add(1);
  bst.add(-10);
  bst.add(-4);
  bst.add(-15);
  bst.printBst();
  std::cout << "Do you find it?" << bst.contains(1) << '\n';
  std::cout << "Do you find it?" << bst.contains(99) << '\n';
  //check remove
  bst.remove(-10);
  std::cout << "Do you find it?" << bst.contains(-10) << '\n';
  bst.printBst();
  BstSet<int> bst2(bst);
  bst2.printBst();
  return EXIT_SUCCESS;
}
