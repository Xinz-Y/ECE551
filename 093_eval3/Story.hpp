#include <cstdlib>
#include <cstring>
#include <set>
#include <sstream>

#include "Page.hpp"
// This method is to update the prev_list field in pges
// meanwhile check if every page has a source to come from
void makePgSource(std::vector<Page> & pages) {
  //iterate every page and find all its sources except page1
  // i =1 becasue we want find sources of pages from page2
  for (size_t i = 1; i < pages.size(); ++i) {
    std::vector<int> Pgsource;
    for (size_t j = 0; j < pages.size(); ++j) {
      for (size_t k = 0; k < pages[j].getPgTogo().size(); ++k) {
        if ((int)i + 1 == pages[j].getPgTogo()[k]) {
          Pgsource.push_back(j);
        }
      }
    }
    // check if any probs 1)pgsource empyt 2)if only one pgsource,can't be itself
    if (Pgsource.empty()) {
      std::cerr << "There is no pages can go to this page" << '\n';
      exit(EXIT_FAILURE);
    }
    if (Pgsource.size() == 1 && (int)i == Pgsource[0]) {
      std::cerr << "There is no other pages(except itself) can go to this page" << '\n';
      exit(EXIT_FAILURE);
    }
    pages[i].setPrev(Pgsource);
  }
}

//for every pages to go in the page, check if it is go beyond the total_pg

class Story {
 private:
  std::vector<Page> pages;
  std::vector<int> win_pages;  //maybe many win pages
  std::vector<int> lose_pages;
  int total_PgNum;

 public:
  Story() : total_PgNum(0){};
  Story & makeStory(const std::string & dirName);
  //  void readStory();
  std::vector<Page> & getPages() { return pages; }
  template<typename container>
  void search(container worklist);
};

Story & Story::makeStory(const std::string & dirName) {
  // go through the whole directory
  std::fstream fs;
  fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  int pg_num = 1;
  // each iteration add a file into story
  while (true) {
    std::string fileName = dirName;
    fileName.append("/page");
    std::stringstream string;
    string << fileName.c_str() << pg_num << ".txt";
    fileName = string.str();
    try {
      fs.open(fileName.c_str(), std::ios_base::in);
      fs.close();
    }
    catch (std::ifstream::failure e) {
      // std::cout << "catch block works" << '\n';
      //if (!fs.is_open()) {
      if (pg_num == 1) {
        std::cerr << "Your directory does not have the page1.txt"
                  << "\n";
        exit(EXIT_FAILURE);
      }
      break;
    }
    // if it is open succesfully, then load the file as normal
    pages.push_back(Page(fileName));
    pg_num++;
  }
  total_PgNum = pages.size();
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
  // check if every page goes to the right pages
  for (size_t i = 0; i < pages.size(); ++i) {
    for (size_t j = 0; j < pages[i].getPgTogo().size(); ++j) {
      // can't be over range;have checked positivity in the page class
      if (pages[i].getPgTogo()[j] > total_PgNum) {
        std::cerr << "One page out of range of the pages in the choice" << '\n';
        exit(EXIT_FAILURE);
      }
    }
  }
  // check if pages have sources add updated the prev_list fields for each page;
  makePgSource(pages);
  //  std::cerr << "All the pages are correct! Load stroy suceessfully!" << '\n';
  return *this;
}

//for step3 we only need to do bfs by queue
template<typename container>
void Story::search(container worklist) {
  std::set<int> visited;
  // the root of the pages is the page1
  std::vector<int> path;
  path.push_back(0);
  //we push the path into the container
  worklist.push(path);
  std::vector<int> currentPath;
  while (!worklist.empty()) {
    currentPath = worklist.peek();
    int currentVer = currentPath[currentPath.size() - 1];
    if (visited.find(currentVer) == visited.end()) {
      pages[currentVer].setDepth(currentPath.size() - 1);
      visited.insert(currentVer);
      if (pages[currentVer].IsLosePg() || pages[currentVer].IsWinPg()) {
        continue;
      }
      for (size_t i = 0; i < pages[currentVer].getPgTogo().size(); i++) {
        currentPath.push_back(pages[currentVer].getPgTogo()[i] - 1);
        worklist.push(currentPath);
        currentPath.pop_back();
      }
    }
  }
}
