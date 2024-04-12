#include "threadedBST.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// output overload
ostream &operator<<(ostream &out, const ThreadedBST &bst) {}

// assignment overload for copying
ThreadedBST &ThreadedBST::operator=(const ThreadedBST &bst) {}

// constructor
// n equals the total number of nodes in the tree
ThreadedBST::ThreadedBST(int n) : totalNodes{n} {
  // vector for adding inputs
  vector<int> nums;
  for (int i = 1; i <= n; i++) {
    nums.push_back(i);
  }
  // assign headptr and start recursive call to build tree, then thread it
  headPtr = buildSubTree(nums, 0, nums.size() - 1);
  threadTree(headPtr);
}

// helper function to thread a tree
void ThreadedBST::threadTree(Node *headPtr) {
  // find left most child of tree
  Node *currentNode = headPtr;
  while (currentNode->leftPtr != nullptr) {
    currentNode = currentNode->leftPtr;
  }
  if (currentNode->rightPtr != nullptr) {
    currentNode = currentNode->rightPtr;
  }
  // traverse tree and create threads when necessary
  while (currentNode->value < totalNodes) {
    if (currentNode->rightPtr == nullptr) { // thread needed
      // create thread and follow it
      currentNode->rightPtr = getEntry(currentNode->value + 1);
      currentNode->isThread = true;
      currentNode = currentNode->rightPtr;
      // new currentNode will always have a right child, follow again
      currentNode = currentNode->rightPtr;
    } else if (currentNode->leftPtr != nullptr) {
      // explore left child/subtree
      currentNode = currentNode->leftPtr;
    } else {
      // explore right child/subtree
      currentNode = currentNode->rightPtr;
    }
  }
}
// helper function to build subtrees recursively
// returns a Node* to make recursion possible
Node *ThreadedBST::buildSubTree(const vector<int> &nums, int lowerIndex,
                                int upperIndex) {

  
  
}
// copy constructor
ThreadedBST::ThreadedBST(const ThreadedBST &tbst) {}

// destructor
ThreadedBST::~ThreadedBST() {}

// clear helper function to recursively delete TBST
void ThreadedBST::clear(Node *node) {}

// searches Tree for a node with specified value
// returns Node if found, nullptr if not found
Node *ThreadedBST::getEntry(int n) const {}

// returns true if empty, false if not
bool ThreadedBST::isEmpty() const { return (headPtr == nullptr); }

// iterator to do inorder traversal of the tree
vector<int> ThreadedBST::inorderTraversal() const {}

// removes a node
Node *ThreadedBST::remove(int value) {}
