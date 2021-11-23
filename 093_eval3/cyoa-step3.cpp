#include <cstdlib>
#include <iostream>
#include <vector>

#include "Story.hpp"
#include "assert.h"
#include "myQueue.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "wrong number of argv" << '\n';
    return EXIT_FAILURE;
  }
  Story sy;
  sy.makeStory(argv[1]);
  myQueue<std::vector<int> > queue;
  sy.search<myQueue<std::vector<int> > >(queue);
  assert(queue.empty());
  std::vector<Page> pages = sy.getPages();
  for (size_t i = 0; i < pages.size(); i++) {
    int dep = pages[i].getDepth();
    if (dep != -1) {
      std::cout << "Page " << i + 1 << ":" << dep << '\n';
    }
    else {
      std::cout << "Page " << i + 1 << " is not reachable" << '\n';
    }
  }

  return EXIT_SUCCESS;
}
