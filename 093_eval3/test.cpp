#include <cstdlib>
#include <iostream>

#include "Story.hpp"
//#include "myQueue.hpp"

int main() {
  Story sy;
  sy.makeStory("story2");
  std::vector<Page> & pages = sy.getPages();
  for (size_t i = 0; i < pages.size(); i++) {
    std::vector<int> prev = pages[i].getPgPrev();
    std::cout << "the length for prev is " << prev.size() << '\n';
    std::cout << "for page " << i + 1 << " the prevlist is ";
    for (size_t k = 0; k < prev.size(); k++) {
      std::cout << prev[k] + 1 << " ";
    }
    std::cout << '\n';
  }
  // myQueue<int> mq;
  // mq.push(1);
  // mq.push(2);
  // std::cout << mq.front() << '\n';
  // std::cout << "now peek the front is " << mq.peek() << '\n';
  // std::cout << "the length is " << mq.size() << '\n';
  // std::cout << "now the front it" << mq.front() << '\n';

  return EXIT_SUCCESS;
}
