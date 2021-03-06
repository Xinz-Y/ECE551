#include <cstdlib>
#include <queue>

template<typename T>
class myQueue : public std::queue<T> {
  //overload peek method
 public:
  T peek() {
    T ans = std::queue<T>::front();
    std::queue<T>::pop();
    return ans;
  }
};
