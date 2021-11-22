#include <cstdlib>
#include <vector>
//#include "Story.hpp"
class Path {
  std::vector<int> path;
  int depth;

 public:
  Path() : depth(0) {}
  int getDepth() const { return depth; }
  void addVer(int ver) {
    path.push_back(ver);
    depth++;
  }
};
