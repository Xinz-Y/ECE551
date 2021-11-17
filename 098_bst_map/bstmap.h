#include <iostream>
#include <stdexcept>

//#include "map.h"
template<typename K, typename V>
class BstMap {
 public:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K key_, V value_) : key(key_), value(value_), left(NULL), right(NULL){};
    ~Node(){};
  };
  Node * root;
  Node * add(Node * current, const K & key, const V & value) {
    // use recursion method
    // base case
    if (current == NULL) {
      Node * temp = new Node(key, value);
      return temp;
    }
    //recursion part: find which node is NULL
    if (key < current->key) {
      // go left
      current->left = add(current->left, key, value);
    }
    else {
      current->right = add(current->right, key, value);
    }
    return current;
  }

 public:
  BstMap() : root(NULL){};
  BstMap(Node * ptr) : root(ptr){};
  virtual void add(const K & key, const V & value) { root = add(root, key, value); }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    // iteration method
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return current->value;
      }
      else if (current->key < key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("key does not exist");
  }

  virtual void remove(const K & key) {
    // iteration methods: pointer to the pointer
    Node ** current = &root;
    while (*current != NULL) {
      //search for the node to move

      if ((*current)->key == key) {
        // three cases to consider
        // left is null
        if ((*current)->left == NULL) {
          Node * temp = (*current)->right;
          delete *current;
          *current = temp;
        }
        else if ((*current)->right == NULL) {
          Node * temp = (*current)->left;
          delete *current;
          *current = temp;
        }
        else {
          // use the smaller similar node to replace
          Node * it = (*current)->left;
          while (it->right != NULL) {
            it = it->right;
          }
          // now it points at the node we want
          //if this node is the direct left child of parent, then the left node pointer of this node should not change
          if (it != (*current)->left) {
            it->left = (*current)->left;
          }
          it->right = (*current)->right;
          delete *current;
          *current = it;
        }
      }
      else {
        if ((*current)->key < key) {
          current = &((*current)->left);
        }
        else {
          current = &((*current)->right);
        }
      }
    }
  }
  void cleanBst(Node * current) {
    while (current != NULL) {
      cleanBst(current->left);
      cleanBst(current->right);
      delete current;
      current = NULL;
    }
  }
  //postoder traversal
  virtual ~BstMap<K, V>() {
    cleanBst(root);
    //delete root;
  }

  // friend std::ostream & operator<<(std::ostream& s,const BstMap & bst){
  //   s <<

  // }
 private:
  void printInorder(Node * current) {
    if (current != NULL) {
      printInorder(current->left);
      std::cout << "The key is " << current->key << " The value is " << current->value
                << '\n';
      std::cout << "the left ptr is " << current->left << "the right pte is "
                << current->right << '\n';
      printInorder(current->right);
    }
  }

 public:
  void printBst() {
    Node * curr = root;
    //    std::cout << "the root points at" << root << "\n";
    printInorder(curr);
  }
};
