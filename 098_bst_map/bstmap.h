#include <iostream>
#include <stdexcept>

#include "assert.h"
#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
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

 public:
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
      Node * newleft = add(current->left, key, value);
      current->left = newleft;
    }
    else {
      Node * newright = add(current->right, key, value);
      current->right = newright;
    }
    return current;
  }

 public:
  BstMap() : root(NULL){};
  //  BstMap(Node * ptr) : root(ptr){};
  virtual void add(const K & key, const V & value) { root = add(root, key, value); }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    // iteration method
    V * ans = NULL;
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        ans = &current->value;
        break;
      }
      else if (current->key > key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    if (ans == NULL) {
      throw std::invalid_argument("key does not exist");
    }
    return *ans;
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
          Node * temp = *current;
          *current = (*current)->right;
          delete temp;
        }
        else if ((*current)->right == NULL) {
          Node * temp = *current;
          *current = (*current)->left;
          delete temp;
        }
        else {
          // use the smaller similar node to replace
          Node ** it = &((*current)->left);
          while ((*it)->right != NULL) {
            it = &(*it)->right;
          }
          if (*it != (*current)->left) {
            (*it)->left = (*current)->left;
          }
          (*it)->right = (*current)->right;
          Node * temp = *current;
          *current = (*it);
          *it = NULL;
          delete temp;
        }
      }
      else {
        if ((*current)->key > key) {
          current = &((*current)->left);
        }
        else {
          current = &((*current)->right);
        }
      }
    }
  }
  virtual void cleanBst(Node * current) {
    if (current != NULL) {
      cleanBst(current->left);
      cleanBst(current->right);
      current->left = NULL;
      current->right = NULL;
      delete current;
    }
  }
  //postoder traversal
  virtual ~BstMap<K, V>() {
    cleanBst(root);
    //delete root;
  }

 private:
  void printInorder(Node * current) {
    if (current != NULL) {
      printInorder(current->left);
      std::cout << "The key is " << current->key << " The value is " << current->value
                << '\n';
      if (current->left != NULL) {
        std::cout << "the left ptr is " << current->left->key << '\n';
      }
      if (current->right != NULL) {
        std::cout << "the right pte is " << current->right->key << '\n';
      }
      printInorder(current->right);
    }
  }

 public:
  void printBst() {
    Node * curr = root;
    //    std::cout << "the root points at" << root << "\n";
    printInorder(curr);
  }

  // Rule of three
  // copy constructor
  void recreate(Node * current) {
    //std::cout << "the root points at " << root << '\n';
    //    assert(root == NULL);
    if (current != NULL) {
      add(current->key, current->value);
      recreate(current->left);
      recreate(current->right);
    }
  }
  BstMap(const BstMap & rhs) : root(NULL) {
    //uses preorder traversal
    Node * current = rhs.root;
    recreate(current);
  }
  // assignment operator
  BstMap & operator=(const BstMap & rhs) {
    BstMap temp(rhs);
    //swap the root
    Node * tempRoot = root;
    root = temp.root;
    temp.root = tempRoot;
    // temp obejct will go away when operator frame disappear
    // cleanBst(root);
    //root = temp.root;
    //temp.root = NULL;
    return *this;
  }
};
