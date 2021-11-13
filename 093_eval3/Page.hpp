#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

//check if a string is only number
bool IsNum(const std::string & s) {
  for (size_t i = 0; i < s.length(); i++) {
    if (std::isdigit(s[i]) == 0) {
      return false;
    }
  }
  return true;
}

class Page {
 private:
  int pg_num;
  //  int * prev_list;
  // int * next_list;
  class Navigation {
   public:
    std::vector<std::pair<int, std::string> > choices;
    // std::pair<int, std::string> choice;
    // added later the methods for Navigation
  };
  class Text {
   public:
    std::vector<std::string> lines;
    // std::string line;
    // added later the methods for Text
  };
  Navigation navi;
  Text tex;

 public:
  // Page() : pg_num(0), prev_list(NULL), next_list(NULL){};
  Page() : pg_num(0){};
  explicit Page(const std::string s);
  friend std::ostream & operator<<(std::ostream & steam, const Page & pg);
};

// for now the prevlist and nextlist are all null
Page::Page(const std::string s) {
  pg_num = std::atoi(s.c_str());
  std::ifstream pg_file;
  pg_file.open(s.c_str());
  // check if file is opened
  if (!pg_file.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }
  std::string line;
  bool navi_comp = false;
  int row = 0;
  while (getline(pg_file, line).good()) {
    // three coner cases for the first line
    if (row == 0) {
      if (line[0] == '#') {
        std::cerr << "There is no navigatio part"
                  << "\n";
        exit(EXIT_FAILURE);
      }
      if (line.compare("LOSE") == 0) {
        navi.choices.push_back(std::pair<int, std::string>(-1, "LOSE"));
        continue;
      }
      if (line.compare("WIN") == 0) {
        navi.choices.push_back(std::pair<int, std::string>(-1, "WIN"));
        continue;
      }
    }
    row++;
    if (line[0] == '#') {
      navi_comp = true;
      continue;
    }
    // load navigation
    if (navi_comp == false) {
      // format check-there is :
      size_t pos = line.find(':');
      if (pos == std::string::npos) {
        std::cerr << "There is no : in one line of navigation part"
                  << "\n";
        exit(EXIT_FAILURE);
      }
      // make sure there is number before :
      if (pos == 0) {
        std::cerr << "There is nothing before : in one line of navigation part"
                  << "\n";
        exit(EXIT_FAILURE);
      }
      std::string first = line.substr(0, pos);
      if (!IsNum(first)) {
        std::cerr
            << "There is something not number before : in one line of navigation part"
            << "\n";
        exit(EXIT_FAILURE);
      }
      int num = std::atoi(first.c_str());
      std::string back = line.substr(pos + 1);
      navi.choices.push_back(std::pair<int, std::string>(num, back));
    }
    //load text
    else {
      tex.lines.push_back(line);
    }
  }
  if (!pg_file.eof() && !pg_file) {
    std::cerr << "Failed to read the page file"
              << "\n";
    exit(EXIT_FAILURE);
  }
}

std::ostream & operator<<(std::ostream & stream, const Page & pg) {
  // print the text of the page
  //iterate through the pg.tex.lines
  for (std::vector<std::string>::const_iterator it = pg.tex.lines.begin();
       it != pg.tex.lines.end();
       ++it) {
    stream << *it << "\n";
  }
  stream << "\n";
  stream << "Waht would you like to do?";
  stream << "\n";
  //print the navigation
  // in the cases of win and lose
  if (pg.navi.choices[0].first == -1) {
    if (pg.navi.choices[0].second.compare("LOSE") == 0) {
      stream << "Congratulations! You have won. Hooray!"
             << "\n";
    }
    else {
      stream << "Sorry, you have lost. Better luck next time!"
             << "\n";
    }
    return stream;
  }
  int index = 1;
  for (std::vector<std::pair<int, std::string> >::const_iterator it =
           pg.navi.choices.begin();
       it != pg.navi.choices.end();
       ++it) {
    stream << " " << index << ". " << (*it).second << "\n";
    index++;
  }

  return stream;
}
