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

  //  More efficient to use thread pointers than bools, otherwise have to check
  //  validity for insertion and traversal also need two b/c one could be real
  //  pointer and the other a thread.
  Node *leftThread = nullptr;
  Node *rightThread = nullptr;

  int height = 1;
  int balanceFactor = 0;
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

  // Removes specific element,
  Node *remove(int value); // Returns true if successful, false if not.

  // Adds new element.
  void add(int value);
  Node *insertNode(Node *&node, int value); // Rec. helper for add.

  int numberOfNodes() const { return totalNodes; }

  // Iterator to do inorder traversal of the tree.
  std::vector<int> inorderTraversal() const;

private:
  Node *headPtr = nullptr; // Root pointer (top of tree).
  int totalNodes = 0;      // Total number of nodes in the tree.

  // Function to delete TBST.
  void clear();

  // Returns true if empty, false if not.
  bool isEmpty() const;

  // Searchs Tree for a node with specified value.
  // Returns Node if found, nullptr if not found.
  Node *getEntry(int n) const;

  // Helper function to build subtrees recursively.
  // Returns a Node* to make recursion possible.
  Node *buildSubTree(const std::vector<int> &nums, int lower, int upper);

  // Helper function to find parent.
  Node *getParent(int n) const;

  // Helper function to get left leaf of root.
  Node *getLeftLeaf(Node *root) const;

  Node *rebalanceTree(Node *root);
  void rebalanceTree();
  int balanceFactor(Node *node);
  int getHeight(Node *node);

  Node *rightRightBalance(Node *root);
  Node *rightLeftBalance(Node *root);
  Node *leftLeftBalance(Node *root);
  Node *leftRightBalance(Node *root);

  // Helper method for overloaded = operator.
  void copyNodes(Node *&dest, Node *src, Node *parent);

  // Helper method for clear.
  void clearNodes(Node *node);

  // Removes a single node from the tree, without deleting it.
  Node *remove(Node *root, int valToRem); // Helper method for remove(int: val).

  int getChildCount(Node *node); // Returns num of children a node has.
  void clearPtrs(Node *node);    // Sets all pointer of node to nullptr.

  void setTraversals(std::vector<int> &preOrderT, std::vector<int> &inOrderT,
                     std::vector<int> &postOrderT) const;
  void traverse(Node *node, std::vector<int> &preOrderT,
                std::vector<int> &inOrderT,
                std::vector<int> &postOrderT) const; // Rescursive helper
};

#endif // THREADEDBST_H
