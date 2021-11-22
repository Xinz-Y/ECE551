#include <cstdlib>
#include <iostream>
#include <vector>

#include "Story.hpp"
#include "assert.h"
#include "myQueue.hpp"
int main() {
  Story sy;
  sy.makeStory("./story1");
  myQueue<std::vector<int> > queue;
  sy.search<myQueue<std::vector<int> > >(queue);
  assert(queue.empty());
  std::vector<Page> pages = sy.getPages();
  for (size_t i = 0; i < pages.size(); i++) {
    int dep = pages[i].getDepth();
    std::cout << "Page " << i + 1 << ":" << dep << '\n';
  }
  return EXIT_SUCCESS;
}
