#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

std::ostream & printLines(std::vector<std::string> lines) {
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
  return std::cout;
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    // read from standard input
    std::vector<std::string> lines;
    std::string line;

    while (getline(std::cin, line).good()) {
      lines.push_back(line);
    }
    if (!std::cin.eof() && !std::cin) {
      std::cerr << "Can not read strings from standard input" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::sort(lines.begin(), lines.end());
    printLines(lines);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::vector<std::string> lines;
      std::string line;

      std::ifstream myfile;
      myfile.open(argv[i]);
      if (!myfile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
      }
      while (getline(myfile, line).good()) {
        lines.push_back(line);
      }
      if (!myfile.eof() && !myfile) {
        std::cerr << "failed to read file" << std::endl;
        exit(EXIT_FAILURE);
      }
      std::sort(lines.begin(), lines.end());
      printLines(lines);
    }
  }
}
