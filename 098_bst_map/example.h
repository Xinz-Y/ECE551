#include <exception>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 protected:
  struct Node {
    K key;
    V value;
    Node *left, *right;
    Node(const K & key, const V & value) :
        key(key),
        value(value),
        left(NULL),
        right(NULL) {}
  };
  Node * root;

 public:
  virtual void add(const K & key, const V & value) {
    Node ** n = lookupNode(key);
    if (*n == NULL) {
      *n = new Node(key, value);
    }
    else {
      (*n)->value = value;
    }
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument);
  BstMap() : root(NULL) {}
  BstMap(const BstMap & m) : root(NULL) { copyTree(&root, m.root); }
  virtual ~BstMap();
};
