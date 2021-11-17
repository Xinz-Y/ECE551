#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> bMap;
  bMap.add(0, 0);
  bMap.add(-4, -4);
  bMap.add(-2, -2);
  bMap.add(-10, -10);
  bMap.add(5, 5);
  bMap.add(7, 7);
  bMap.add(4, 4);
  bMap.add(-100, -100);
  bMap.add(-6, -6);
  bMap.add(1, 1);
  bMap.add(6, 6);
  bMap.add(11, 11);
  bMap.printBst();
  std::cout << "((((((((((((((((((((" << '\n';
  std::cout << "Now start to remove " << '\n';
  ;
  // bMap.remove(-1);
  //bMap.remove(7);
  // bMap.printBst();
  std::cout << '\n';
  //bMap.remove(10);
  //bMap.remove(1);
  //  bMap.remove(10111);
  //  int val = bMap.lookup(5);
  //std::cout << "FInd the value for key 5 is " << val << '\n';
  try {
    int val = bMap.lookup(99);
    std::cout << "find the value for key 99 is" << val << "\n";
  }
  catch (std::invalid_argument & e) {
    std::cout << "cant find the value for 99 " << e.what() << "\n";
  }
  //bMap.printBst();
  //bMap.remove(-5);
  return EXIT_SUCCESS;
}
