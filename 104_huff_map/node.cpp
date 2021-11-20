#include "node.h"

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //posteroder
  if (left != NULL) {
    left->buildMap(b.plusZero(), theMap);
  }
  if (right != NULL) {
    right->buildMap(b.plusOne(), theMap);
  }
  //base case
  if (sym != NO_SYM) {
    theMap[sym] = b;
  }
}
