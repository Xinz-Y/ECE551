#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

typedef LinkedList<int> IntList;
class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(1);
    // only one element
    assert(il.head == il.tail);
    assert(il.head->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    il.addFront(2);
    // test two elements
    // check head is right
    assert(il.head->data == 2);
    // check tail is right
    assert(il.tail->data == 1);
    //check tail node's next is null
    assert(il.tail->next == NULL);
    //check tail node's previous node is right
    assert(il.tail->prev->data == 2);
    //check head node's prev is null
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 1);
  }
  // testAddBack()
  void testAddBack() {
    IntList il;
    il.addBack(1);
    // only one element
    assert(il.head == il.tail);
    assert(il.head->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    il.addBack(2);
    // test two elements
    // check head is right
    assert(il.head->data == 1);
    // check tail is right
    assert(il.tail->data == 2);
    //check tail node's next is null
    assert(il.tail->next == NULL);
    //check tail node's previous node is right
    assert(il.tail->prev->data == 1);
    //check head node's prev is null
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
  }
  void testRuleofThree() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    IntList il2(il);
    // check if the copy constructor works
    assert(il2.head->data == il.head->data);
    assert(il2.tail->data == il.tail->data);
    // check if the first node of il2 same as il
    assert(il2.head->next->data == il.head->next->data);
    assert(il2.head->prev == il.head->prev);  //they should be NULL
    // check if the second node of il2 same as il
    assert(il2.tail->next == il.tail->next);
    assert(il2.tail->prev->data = il.tail->prev->data);
    IntList il3;
    il3 = il;
    // check if the assignment works
    assert(il3.head->data == il.head->data);
    assert(il3.tail->data == il.tail->data);
    // check if the first node of il2 same as il
    assert(il3.head->next->data == il.head->next->data);
    assert(il3.head->prev == il.head->prev);  //they should be NULL
    // check if the second node of il2 same as il
    assert(il3.tail->next == il.tail->next);
    assert(il3.tail->prev->data = il.tail->prev->data);

    // check destucotr
    il2.addBack(3);
    il = il2;
  }
  void testRemovals() {
    IntList il;
    assert(il.remove(999999) == false);
    il.addBack(1);
    assert(il.remove(1) == true);
    // check if the list be empty
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);

    il.addBack(1);
    il.addBack(2);
    il.addBack(3);
    // delete the head
    assert(il.remove(1) == true);

    assert(il.head->data == 2);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
    assert(il.head->next->data == 3);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 2);
    // delte the tail
    il.addFront(1);
    il.remove(3);

    assert(il.head->data == 1);
    assert(il.tail->data == 2);
    assert(il.head->next->data == 2);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 1);
    assert(il.getSize() == 2);
    il.remove(2);
    assert(il.remove(2) == false);
    assert(il.remove(100) == false);
    assert(il.head->data == 1);
    assert(il.tail->data == 1);
    assert(il.getSize() == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    // delete the middle
    il.addBack(2);
    il.addBack(3);
    il.remove(2);
    assert(il.head->next->data == 3);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
  }
  void testOperator() {
    IntList il;
    const IntList * ptr = &il;
    il.addFront(1);
    il.addFront(2);
    il.addFront(3);
    assert((*ptr)[0] == 3);
    assert((*ptr)[1] == 2);
    assert((*ptr)[2] == 1);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  std::cout << "test constructor is right" << '\n';
  t.testAddFront();
  std::cout << "test add Front is right" << '\n';
  t.testAddBack();
  std::cout << "test addBack is right" << '\n';
  t.testOperator();
  std::cout << "test [] is right" << '\n';
  t.testRuleofThree();
  std::cout << "Ro3 is right" << '\n';

  t.testRemovals();
  std::cout << "test remove is right" << '\n';

  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
