#include <cstdlib>
#include <iostream>

#include "bstmap.h"
int main() {
  typedef BstMap<int, int>::Node Node;
  BstMap<int, int> bst;
  bst.add(1, 1);
  bst.add(2, 2);
  bst.add(-1, -1);
  Node ** current = &(bst.root);
  // Node ** it = &((*current)->left);
  Node * it = (*current)->left;
  delete *current;
  *current = it;

  return EXIT_SUCCESS;
}
