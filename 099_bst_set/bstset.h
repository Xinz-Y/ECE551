#include <cstdlib>
#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & key_) : key(key_), left(NULL), right(NULL){};
  };
  Node * root;
  Node * add(Node * current, const T & key) {
    //base case
    if (current == NULL) {
      Node * temp = new Node(key);
      return temp;
    }
    if (current->key == key) {
      return current;
    }
    // recursion
    if (current->key > key) {
      current->left = add(current->left, key);
    }
    else {
      current->right = add(current->right, key);
    }
    return current;
  }
  bool contains(Node * current, const T & key) const {
    bool ans;
    if (current == NULL) {
      return false;
    }
    if (current->key == key) {
      return true;
    }
    if (current->key > key) {
      ans = contains(current->left, key);
    }
    else {
      ans = contains(current->right, key);
    }
    return ans;
  }

  Node * remove(Node * current, const T & key) {
    // those are base cases which give the return
    if (current == NULL) {
      return current;
    }
    if (current->key == key) {
      //three cases
      if (current->left == NULL) {
        Node * temp = current->right;
        delete current;
        return temp;
      }
      else if (current->right == NULL) {
        Node * temp = current->left;
        delete current;
        return temp;
      }
      else {
        // find the smaller most similar node
        Node ** it = &(current->left);
        while ((*it)->right != NULL) {
          it = &((*it)->right);
        }
        //find the node
        Node * downNode = (*it)->left;
        if (*it != current->left) {
          (*it)->left = current->left;
        }
        (*it)->right = current->right;
        Node * temp = *it;
        //current = *it;
        *it = downNode;
        delete current;
        return temp;
      }
    }
    // now recursion steps
    if (current->key > key) {
      current->left = remove(current->left, key);
    }
    else {
      current->right = remove(current->right, key);
    }
    return current;
  }
  void destroy(Node * current) {
    //postorder
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
  void copyTree(const Node * current) {
    //preorder
    if (current != NULL) {
      add(current->key);
      copyTree(current->left);
      copyTree(current->right);
    }
  }
  void printBst(Node * current) const {
    if (current != NULL) {
      printBst(current->left);
      std::cout << "The key for this node is " << current->key << "\n";
      if (current->left != NULL) {
        std::cout << "The left node is " << current->left->key << '\n';
      }
      if (current->right != NULL) {
        std::cout << "The right node is " << current->right->key << '\n';
      }
      printBst(current->right);
    }
  }

 public:
  BstSet<T>() : root(NULL){};
  virtual void add(const T & key) { root = add(root, key); }
  virtual bool contains(const T & key) const {
    bool ans = contains(root, key);
    return ans;
  }

  virtual void remove(const T & key) { root = remove(root, key); }

  virtual ~BstSet<T>() { destroy(root); }
  //Rule of three
  //copy construcotr
  BstSet(const BstSet & rhs) : root(NULL) {
    //preorder
    copyTree(rhs.root);
  }

  // assignment operator
  BstSet & operator=(const BstSet & rhs) {
    BstSet temp(rhs);
    Node * tempRoot = root;
    root = temp.root;
    temp.root = tempRoot;
    return *this;
  }
  void printBst() const { printBst(root); }
  //friend std::ostream & operator<<(std::ostream & os, const BstSet & bst);
};
