#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;
  //make a priority queue
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() != 1) {
    // build the tree bt poping the top two nodes in the pq
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();
    // the parent node of these two nodes
    Node * parent = new Node(left, right);
    pq.push(parent);
  }
  // now only one node left which is the root for our tree
  return pq.top();
}
