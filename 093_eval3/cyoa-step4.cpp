#include <cstdlib>
#include <iostream>
#include <vector>

#include "Story.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong number of argv" << '\n';
    return EXIT_FAILURE;
  }

  Story sy;
  sy.makeStory(argv[1]);
  std::vector<std::vector<std::pair<int, int> > > sucPath = sy.findAcyclicPath();
  if (sucPath.empty()) {
    std::cout << "This story is unwinnable!" << '\n';
    return EXIT_SUCCESS;
  }
  for (size_t i = 0; i < sucPath.size(); i++) {
    for (size_t j = 0; j < sucPath[i].size(); j++) {
      if (j == sucPath[i].size() - 1) {
        std::cout << sucPath[i][j].first + 1 << "(win)" << '\n';
        continue;
      }
      std::cout << sucPath[i][j].first + 1 << "(" << sucPath[i][j + 1].second + 1 << ")"
                << ",";
    }
  }

  return EXIT_SUCCESS;
}
