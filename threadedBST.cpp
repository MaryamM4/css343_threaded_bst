/**
 * Threaded Binary Search Tree (TBST).
 */

#include "threadedBST.h"
#include <algorithm>
#include <iostream>
#include <vector>

/**
 * Constructor.
 *
 * @param: n equals the total number of nodes in the tree.
 */
ThreadedBST::ThreadedBST(int n) : totalNodes{n} {
  std::vector<int> nums; // For adding inputs.

  for (int i = 1; i <= n; i++) {
    nums.push_back(i);
  }

  // Assign headptr and start recursive call to build tree,
  headPtr = buildSubTree(nums, 0, nums.size() - 1);

  // then thread it.
  threadTree(headPtr);
}

/**
 * Copy Constructor.
 */
ThreadedBST::ThreadedBST(const ThreadedBST &tbst) {
  std::vector<int> nums = tbst.inorderTraversal();

  // Assign headptr and start recursive call to build tree,
  headPtr = buildSubTree(nums, 0, nums.size() - 1);

  // then thread it.
  threadTree(headPtr);
}

/**
 * Destructor.
 */
ThreadedBST::~ThreadedBST() { clear(headPtr); }

/**
 * Output overload.
 */
std::ostream &operator<<(std::ostream &out, const ThreadedBST &bst) {}

/**
 * Assignment overload for copying.
 */
ThreadedBST &ThreadedBST::operator=(const ThreadedBST &bst) {}

/**
 * @note Helper function to thread a tree.
 */
void ThreadedBST::threadTree(Node *headPtr) {
  // find left most child of tree
  Node *currentNode = headPtr;
  while (currentNode->leftPtr != nullptr) {
    currentNode = currentNode->leftPtr;
  }
  if (currentNode->rightPtr != nullptr) {
    currentNode = currentNode->rightPtr;
  }

  // Traverse tree and create threads when necessary.
  while (currentNode->value < totalNodes) {
    if (currentNode->rightPtr == nullptr) { // Thread needed.
      // Create thread and follow it
      currentNode->rightPtr = getEntry(currentNode->value + 1);
      currentNode->isThread = true;
      currentNode = currentNode->rightPtr;

      // New currentNode will always have a right child, follow again.
      currentNode = currentNode->rightPtr;

    } else if (currentNode->leftPtr != nullptr) {
      // Explore left child/subtree.
      currentNode = currentNode->leftPtr;

    } else {
      // Explore right child/subtree.
      currentNode = currentNode->rightPtr;
    }
  }
}

/**
 * @note   Helper function to recusivley build subtrees.
 * @return A node ptr to make recursion possible.
 */
Node *ThreadedBST::buildSubTree(const std::vector<int> &nums, int lowerIndex,
                                int upperIndex) {}

/**
 * Searches the tree for a node with specified value n.
 *
 * @return Node pointer if found, nullptr if not found.
 */
Node *ThreadedBST::getEntry(int n) const {}

/**
 * Removes first found node with the given value from the tree.
 * Does NOT delete the node or it's pointer.
 *
 * @return Pointer to the node that has been remove from the tree.
 *         Return nullptr if value DNE in tree.
 */
Node *ThreadedBST::remove(int value) {}

/**
 * Clear function to recusivley delete TBST.
 * @note Helper function for destructor.
 */
void ThreadedBST::clear(Node *node) {}

/**
 * @pre If the tree is empty, the headPtr is set to nullptr.
 * @return True if the tree is empty, false if not.
 */
bool ThreadedBST::isEmpty() const { return (headPtr == nullptr); }

/**
 * Iterator for in-order traversal of the tree.
 */
std::vector<int> ThreadedBST::inorderTraversal() const {}
