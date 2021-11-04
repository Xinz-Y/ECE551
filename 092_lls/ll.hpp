#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    // Node(){};
    Node(const T & data_, Node * next_, Node * prev_) :
        data(data_),
        next(next_),
        prev(prev_){};
  };

 public:
  Node * head;
  Node * tail;
  int size;

 public:
  friend class Tester;
  LinkedList() : head(NULL), tail(NULL), size(0){};
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    // we need to change the pointer in the old head
    // the next node pointer of the old head node does not change
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  // use recursive method for it
 private:
  //helper function
  Node * remove(const T & item, Node * curr) {
    //this means at the end of the list, no find the item. return the original list
    if (curr == NULL) {
      return NULL;
    }
    // find the item, we delete it
    if (item == curr->data) {
      // update the tail pointer if the curr is the tail
      Node * temp = curr->next;
      // we need to update the prev pointer of temp
      if (tail == curr) {
        tail = curr->prev;
      }
      else {
        temp->prev = curr->prev;
      }
      delete curr;
      size--;
      return temp;
    }
    // recursive call
    // current node is not deleted, to see if next node going to be deleted
    curr->next = remove(item, curr->next);
    return curr;
  }

 public:
  bool remove(const T & item) {
    int size_before = size;
    head = remove(item, head);
    int size_now = size;
    if (size_before == size_now) {
      return false;
    }
    return true;
  }

 private:
  class accessError : public std::exception {
   public:
    const char * what() { return "Index out of boundd"; }
  };

 public:
  T & operator[](int index) {
    try {
      if (index >= size || index < 0) {
        throw accessError();
      }
    }
    catch (accessError & e) {
      std::cout << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    Node * target = head;
    for (int i = 1; i <= index; i++) {
      target = target->next;
    }
    T & ans = target->data;
    return ans;
  }

  const T & operator[](int index) const {
    try {
      if (index >= size || index < 0) {
        throw accessError();
      }
    }
    catch (accessError & e) {
      std::cout << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    Node * target = head;
    for (int i = 1; i <= index; i++) {
      target = target->next;
    }
    const T & ans = target->data;
    return ans;
  }

  int find(const T & item) const {
    for (int i = 0; i < size; i++) {
      // use [] to check if equal
      // const LinkedList * ptr = this;
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }
  // copy constructor
  LinkedList(const LinkedList<T> & list) : head(NULL), tail(NULL), size(0) {
    // create a const ptr
    for (int i = 0; i < list.size; i++) {
      const T & dataToadd = list[i];
      addBack(dataToadd);
    }
  }
  // use swap
  LinkedList & operator=(const LinkedList<T> & rhs) {
    LinkedList temp(rhs);
    Node * head_temp = head;
    Node * tail_temp = tail;
    head = temp.head;
    tail = temp.tail;
    temp.head = head_temp;
    temp.tail = tail_temp;
    size = rhs.size;
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  int getSize() const { return size; }
};

#endif
