#include <cstdlib>
#include <iostream>

#include "Page.hpp"

int main(int argc, char ** argv) {
  // initialization the page object
  if (argc != 2) {
    std::cerr << "Wrong number of argv"
              << "\n";
    return EXIT_FAILURE;
  }
  Page pg(argv[1]);

  //int main() {
  // Page pg("./story1/page11.txt");
  std::cout << pg;
  // std::vector<int> ans = pg.getPgTogo();
  // for (size_t i = 0; i < ans.size(); ++i) {
  //   std::cout << "pages to go are" << ans[i] << '\n';
  // }
  return EXIT_SUCCESS;
}
