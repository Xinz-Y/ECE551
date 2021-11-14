#include <cstdlib>
#include <iostream>

#include "Story.hpp"

class InputError : public std::exception {
 public:
  const char * what() const throw() {
    return "That is not a valid choice, please try again";
  }
};

int ConvertInput(const Page & current, std::string line) {
  int choice_num = 0;
  //check the input is number and a valid choice
  try {
    // without this if, empty line will be regarded as 0
    if (line.empty()) {
      throw InputError();
    }
    if (!IsNum(line)) {
      throw InputError();
    }
    choice_num = std::atoi(line.c_str());
    if ((size_t)choice_num > current.getPgTogo().size()) {
      throw InputError();
    }
  }
  catch (InputError & e) {
    std::cout << e.what() << '\n';
    getline(std::cin, line);
    choice_num = ConvertInput(current, line);
  }

  return choice_num;
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong number of argv" << '\n';
    return EXIT_FAILURE;
  }
  Story sy;
  sy.makeStory(argv[1]);
  // now we begin to read the story
  std::vector<Page> & pages = sy.getPages();
  Page & current = pages[0];
  while (!current.IsWinPg() && !current.IsLosePg()) {
    std::cout << "Current page is " << current.getPgNum() << '\n';
    std::cout << current;
    // read from the standard input
    std::string line;
    getline(std::cin, line);
    if (!std::cin.eof() && !std::cin) {
      std::cerr << "Can not read strings from the standard input" << '\n';
      exit(EXIT_FAILURE);
    }
    int choice_num = 0;
    //check the input is number and a valid choice
    choice_num = ConvertInput(current, line);
    int act_pg_num = current.getPgTogo()[choice_num - 1];
    current = pages[act_pg_num];
  }
  // this page is win or lose
  std::cout << "Current page is " << current.getPgNum() << '\n';
  std::cout << current;
  return EXIT_SUCCESS;
}
