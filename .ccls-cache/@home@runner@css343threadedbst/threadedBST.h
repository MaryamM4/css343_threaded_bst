/*
File name: threadedBST.h
Name: Mikhail Ermolenko, Mike Jansen, Tyler Tran
Date: December 11, 2021
This header file contains signatures for all functions and variables.
*/

#ifndef THREADEDBST_H
#define THREADEDBST_H

#include <iostream>
#include <vector>

class Node {
  friend class ThreadedBST;

private:
  int value;

  Node *leftPtr = nullptr;
  Node *rightPtr = nullptr;

  bool isThread = false; // Nodes point at thread OR child.
};

class ThreadedBST {
  // Output overload.
  friend std::ostream &operator<<(std::ostream &out, const ThreadedBST &bst);

public:
  // n equals the total number of nodes in the tree
  explicit ThreadedBST(int n);          // Constructor.
  ThreadedBST(const ThreadedBST &tbst); // Copy constructor.
  ~ThreadedBST();                       // Destructor.

  // Assignment overload for copying.
  ThreadedBST &operator=(const ThreadedBST &bst);

  // Helper function for copy constructor.
  Node *copyNode(Node *newNode, Node *oldNode);

  // Helper function to find parent.
  Node *getParent(int n) const;

  // Removes specific element,
  Node *remove(int value); // Returns true if successful, false if not.

  // Iterator to do inorder traversal of the tree.
  std::vector<int> inorderTraversal() const;

private:
  Node *headPtr = nullptr; // Root pointer (top of tree).
  int totalNodes;          // Total number of nodes in the tree.

  // Helper function to thread a tree.
  void threadTree(Node *headPtr);

  // clear helper function to recursively delete TBST.
  void clear(Node *node);

  // Returns true if empty, false if not.
  bool isEmpty() const;

  // Searchs Tree for a node with specified value.
  // Returns Node if found, nullptr if not found.
  Node *getEntry(int n) const;

  // Helper function to build subtrees recursively.
  // Returns a Node* to make recursion possible.
  Node *buildSubTree(const std::vector<int> &nums, int lower, int upper);
};

#endif
