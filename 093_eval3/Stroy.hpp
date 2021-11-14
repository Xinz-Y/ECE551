#include <cstdlib>
#include <cstring>

#include "Page.hpp"
// check if every pages goes to the right pages
//void CheckGoRgiht(const S & pages){
//for evvery pages to go in the page, check if it is go beyond the total_pg

class Story {
 private:
  //Page * head;
  // Page * win_page;
  // Page * lose_page;
  std::vector<Page> pages;
  std::vector<int> win_pages;  //maybe many win pages
  std::vector<int> lose_pages;
  int total_PgNum;

 public:
  Story() : total_PgNum(0){};
  Story & makeStory(const std::string & dirName) {
    // go through the whole directory
    std::fstream fs;
    int pg_num = 1;
    // each iteration add a file into story
    while (true) {
      std::string fileName = dirName;
      fileName.append("page");
      fileName.append(std::to_string(pg_num));
      fs.open(fileName);
      if (!fs.is_open()) {
        if (pg_num == 1) {
          std::cerr << "Your directory does not have the page1.txt"
                    << "\n";
          exit(EXIT_FAILURE);
        }
        std::cout << "Load the dir is finished!" << '\n';
        break;
      }
      // if it is open succesfully, then load the file as normal
      pages.push_back(Page(fileName));
      total_PgNum++;
      pg_num++;
    }
    // now we need to find which one is the winPg and the losePg one
    for (std::vector<Page>::const_iterator it = pages.begin(); it != pages.end(); ++it) {
      if ((*it).IsWinPg()) {
        win_pages.push_back((*it).getPgNum());
      }
      else if ((*it).IsLosePg()) {
        lose_pages.push_back((*it).getPgNum());
      }
    }
    if (win_pages.empty()) {
      std::cerr << "There is no win pages in the directory!" << '\n';
      exit(EXIT_FAILURE);
    }
    if (lose_pages.empty()) {
      std::cerr << "There is no lose pages in the directory!" << '\n';
      exit(EXIT_FAILURE);
    }
    //for evvery pages to go in the page, check if it is go beyond the total_pg

    return *this;
  }
};
