#include <cstdlib>
#include <iostream>

#include "bstmap.h"
#include "map.h"

int main() {
  //Map<int, int> * ptr = new BstMap<int, int>();
  //ptr->add(0, 0);
  //ptr->add(-4, -4);
  //ptr->remove(0);
  BstMap<std::string, std::string> b1;
  b1.add("ssss", "222");
  b1.add("bbbs", "sdawd");
  b1.add("aaaa", "2133333s");
  b1.printBst();
  std::cout << "now below is b2" << '\n';
  BstMap<std::string, std::string> b2(b1);
  b2.printBst();
  b2.add("ccccc", "huadhuawd");

  b1 = b2;
  std::cout << "NOw is b1" << '\n';
  b1.printBst();

  //std::cout << "assignment finishes " << '\n';
  //bMap.remove(7);
  // bMap.printBst();
  //  std::cout << '\n';
  //bMap.remove(10);
  //bMap.remove(1);
  //  bMap.remove(10111);
  //  int val = bMap.lookup(5);
  //std::cout << "FInd the value for key 5 is " << val << '\n';
  /*try {
    int val = ptr->lookup(99);
    std::cout << "find the value for key 99 is" << val << "\n";
  }
  catch (std::invalid_argument & e) {
    std::cout << "cant find the value for 99 " << e.what() << "\n";
    }*/
  //delete ptr;
  //bMap.printBst();
  //bMap.remove(-5);

  return EXIT_SUCCESS;
}
