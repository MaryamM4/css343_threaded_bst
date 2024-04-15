/**
 * (Double) Threaded Binary Search Tree (D-TBST).
 * Self-balancing AVL tree.
 *
 * REQS:
 *  - The TBST must be self-balancing.
 *
 * 1. Constructors: Empty, 1 parameter and Copy Constructor
 * 2. Destructor, clear
 * 3. isEmpty, getHeight, numberOfNodes, getEntry(int)
 * 4. operator==,  operator<<
 * 5. add and removal have to be O(log(n))
 * 6. inorder, preorder and post order traversal
 * 7. rebalance. can be O(n)
 * 8-12. No mem. leaks, efficiency & complexity, and proper conding style.
 *
 * OTHER REFERENCES:
 * (1) https://www.geeksforgeeks.org/double-threaded-binary-search-tree/#
 * (2) https://www.geeksforgeeks.org/introduction-to-avl-tree/#
 *
 * =================
 * Starting code provided in CS 343 HW2 specifications.
 * Completions implemented by Maryam M, 2024.
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
}

/**
 * Copy Constructor.
 */
ThreadedBST::ThreadedBST(const ThreadedBST &tbst) {
  std::vector<int> nums = tbst.inorderTraversal();

  // Assign headptr and start recursive call to build tree,
  headPtr = buildSubTree(nums, 0, nums.size() - 1);
}

/**
 * Destructor.
 */
ThreadedBST::~ThreadedBST() { clear(); }

/**
 * Output overload.
 */
std::ostream &operator<<(std::ostream &out, const ThreadedBST &bst) {
  std::vector<int> preOrderT, inOrderT, postOrderT;
  bst.setTraversals(preOrderT, inOrderT, postOrderT);

  out << std::endl << "Pre-order : ";
  for (int val : preOrderT) {
    out << val << " ";
  }
  out << std::endl;

  out << std::endl << "In-order  : ";
  for (int val : inOrderT) {
    out << val << " ";
  }
  out << std::endl;

  out << std::endl << "Post-order: ";
  for (int val : postOrderT) {
    out << val << " ";
  }
  out << std::endl;
  out << std::endl;

  out << "In Order Traversal using Threading: ";
  std::vector<int> threadedInOrderT = bst.inorderTraversal();

  for (int val : threadedInOrderT) {
    out << val << " ";
  }
  out << std::endl;

  return out;
}

/**
 * Assignment overload for copying.
 */
ThreadedBST &ThreadedBST::operator=(const ThreadedBST &bst) {
  if (this == &bst) {
    return *this; // Self-assignment, no need to do anything
  }

  clear(); // Clear the current tree

  // Perform a deep copy of the bst tree
  if (bst.headPtr == nullptr) {
    return *this; // bst is empty, no need to copy
  }

  // Copy the head node
  headPtr = new Node();
  headPtr->value = bst.headPtr->value;

  // Copy the rest of the tree
  copyNodes(headPtr->leftPtr, bst.headPtr->leftPtr, headPtr);

  return *this;
}

void ThreadedBST::copyNodes(Node *&dest, Node *src, Node *parent) {
  if (src == nullptr) {
    dest = nullptr;
    return;
  }

  dest = new Node();
  dest->value = src->value;
  /// dest->isThread = src->isThread;

  // Update threading pointers
  if (src->leftPtr == parent) {
    dest->leftPtr = parent;
  } else {
    copyNodes(dest->leftPtr, src->leftPtr, src);
  }

  if (src->rightPtr == parent) {
    dest->rightPtr = parent;
  } else {
    copyNodes(dest->rightPtr, src->rightPtr, src);
  }
}

/**
 * @note   Helper function to recusivley build subtrees.
 * @reqs   Add has to be O(log(n)).
 * @return A node ptr to make recursion possible.
 */
Node *ThreadedBST::buildSubTree(const std::vector<int> &nums, int lowerIndex,
                                int upperIndex) {

  // Placeholder. TODO.
  for (int newVal : nums) {
    add(newVal);
  }
  return headPtr;
}

/**
 * Searches the tree for a node with specified value n.
 *
 * @return Node pointer if found, nullptr if not found.
 */
Node *ThreadedBST::getEntry(int n) const {
  Node *currNode = headPtr->leftPtr;

  // Head to left-most leaf. Can't use getLeftLeaf function
  // because we need to check the value of every node we traverse.
  while (currNode != headPtr) {
    if (currNode->value == n) {
      return currNode; // Found the node with value n
    }

    // Move to the next node
    if (currNode->rightPtr != nullptr) { // rightPtr is a child.
      currNode = currNode->rightPtr;

    } else { // rightPtr is a thread.
      currNode = currNode->rightPtr;

      // while (currNode != headPtr && currNode->isThread) {
      //  currNode =
      //       currNode->leftPtr; // Move to the leftmost node of the subtree
      //}
    }
  }

  // At this point, no Node with value n found.
  return nullptr;
}

/**
 * Adds a node with the value to the tree.
 * @note   Rebalances the tree after addition.
 * @reqs   Add has to be O(log(n)), rebalance may be O(n).
 */
void ThreadedBST::add(int value) {
  // std::cout << "add(" << value << ")" << std::endl; // Delete me.

  // Special case: List is empty.
  if (headPtr == nullptr) {
    headPtr = new Node();
    headPtr->value = value;
    headPtr->leftThread = nullptr;
    headPtr->rightThread = nullptr;

    return;
  }

  // Iterate.
  Node *valueParent = headPtr;
  Node *newNode = new Node();
  newNode->value = value;

  while (valueParent != nullptr) {
    if (valueParent->value > value) { // Traverse left.
      if (valueParent->leftPtr == nullptr) {
        valueParent->leftPtr = newNode;
        valueParent->leftThread = newNode;

        newNode->leftThread = nullptr;
        newNode->rightThread = valueParent;

        break;
      }

      valueParent = valueParent->leftPtr;

    } else { // Traverse right.
      if (valueParent->rightPtr == nullptr) {
        valueParent->rightPtr = newNode;
        valueParent->rightThread = newNode;

        newNode->rightThread = nullptr;
        newNode->leftThread = valueParent;

        break;
      }

      valueParent = valueParent->rightPtr;
    }
  }

  rebalanceTree();
  totalNodes++;
}

/**
 * Rebalances the tree if needed.
 *
 * @req     May take O(n) time.
 * @return  Pointer to root node.
 */
void ThreadedBST::rebalanceTree() { headPtr = rebalanceTree(headPtr); }

Node *ThreadedBST::rebalanceTree(Node *root) {
  // Base case: Leaf height is 0.
  if (root == nullptr) {
    return nullptr;
  }

  int leftHeight = 0;
  int rightHeight = 0;
  root->leftPtr = rebalanceTree(root->leftPtr);
  root->rightPtr = rebalanceTree(root->rightPtr);
  if (root->leftPtr) {
    leftHeight = root->leftPtr->height;
  }
  if (root->rightPtr) {
    rightHeight = root->rightPtr->height;
  }

  root->height = 1 + std::max(leftHeight, rightHeight);
  root->balanceFactor = leftHeight - rightHeight;

  if (root->balanceFactor > 1) { //         =========== LEFT-? Heavy.
    if (root->leftPtr->balanceFactor >= 0) {
      std::cout << "[rebalanceTree(" << root->value
                << ")] left-left heavy: right rotation." << std::endl;
      return leftLeftBalance(root); // Right rotation.

    } else { // if rootLeftBF < 0:
      std::cout << "[rebalanceTree(root: " << root->value
                << ")] left-right heavy: left-right rotation." << std::endl;
      return leftRightBalance(root); // Left, right rotations.
    }

  } else if (root->balanceFactor < -1) { // =========== RIGHT-? Heavy.
    if (root->rightPtr->balanceFactor <= 0) {
      std::cout << "[rebalanceTree(" << root->value
                << ")] right-right heavy: left rotation." << std::endl;
      return rightRightBalance(root); // Left rotation.

    } else { // If rootRightBf > 0:
      std::cout << "[rebalanceTree(" << root->value
                << ")] right-left heavy: right-left rotation." << std::endl;
      return rightLeftBalance(root); // Right, left rotations.
    }
  }

  return root;
}

/**
 * @return An int representing the balance factor of the node.
 *         -1 (), 0 (), and 1 ().
 */
int ThreadedBST::balanceFactor(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  int leftHeight = 0;
  int rightHeight = 0;

  if (node->leftPtr != nullptr) {
    leftHeight = node->leftPtr->height;
  }

  if (node->rightPtr != nullptr) {
    rightHeight = node->rightPtr->height;
  }

  return (leftHeight - rightHeight);
}

/**
 * Removes first found node with the given value from the tree.
 * Does NOT delete the node or it's pointer.
 *
 * @reqs   Remove has to be O(log(n)), rebalance may be O(n).
 * @note   Rebalanced the tree after removal.
 * @return Pointer to the node that has been removed from the tree.
 *         Return nullptr if value DNE in tree.
 */
Node *ThreadedBST::remove(int value) {
  Node *removeNode;
  removeNode = remove(headPtr, value);

  if (removeNode != nullptr) {
    totalNodes--;
  }

  rebalanceTree();
  return removeNode;
}

/**
 * @note   Does NOT rebalance the tree.
 * @note   Recursive helper method for remove(int val).
 * @return Pointer to the node that has been removed from the tree,
 *         with it's pointers (children and threads) set to nullptr.
 *         Return nullptr if node DNE in tree.
 */
Node *ThreadedBST::remove(Node *subHead, int valToRem) {

  // Edge case: Fail.
  if (subHead == nullptr) {
    return nullptr;
  }
  Node *returnNode = nullptr;

  // Edge case: Head has value:
  if (headPtr->value == valToRem) {
    returnNode = headPtr;

    int nodeToRemChildCount = getChildCount(returnNode);

    if (nodeToRemChildCount == 0) { // Leaf case.
      headPtr = nullptr;

    } else if (nodeToRemChildCount == 2) { // Double-children case.
      returnNode = headPtr;

      // find a largest node on left side (so it won't have a right ptr) and
      // make it the head
      Node *largest = headPtr->leftPtr;
      Node *largestParent = nullptr;

      while ((largest->rightPtr)) {
        largestParent = largest;
        largest = largest->rightPtr;
      }
      if (largestParent) {
        largestParent->rightPtr = largest->leftPtr;
        largest->leftPtr = returnNode->leftPtr;
      }

      headPtr = largest;
      largest->rightPtr = returnNode->rightPtr;
      largest->rightThread = returnNode->rightThread;

    } else {                           // Single child case.
      if (nodeToRemChildCount == -1) { // Single-left child case.
        headPtr = returnNode->leftPtr;

        // find if there is a right thread pointing to what is being deleted and
        // clear it
        for (Node *currentNode = headPtr; currentNode;
             currentNode = currentNode->rightThread) {
          if (currentNode->rightThread == returnNode) {
            currentNode->rightThread = nullptr;
            break;
          }
        }

      } else if (nodeToRemChildCount == 1) { // Single-right child case.
        headPtr = returnNode->rightPtr;

        // find if there is a left thread pointing to what is being deleted and
        // clear it
        for (Node *currentNode = headPtr; currentNode;
             currentNode = currentNode->leftThread) {
          if (currentNode->leftThread == returnNode) {
            currentNode->leftThread = nullptr;
            break;
          }
        }
      }
    }

    clearPtrs(returnNode); // Clear removed node's access to tree.
    return returnNode;
  }

  if (subHead->value == valToRem) {
    return subHead;
  } else if (subHead->value >
             valToRem) { //     Look left. =================== LEFT
    Node *nextNode = subHead->leftPtr;

    if (nextNode == nullptr) {
      return nullptr; // valToDelete DNE in tree. Case: Fail.

    } else if (nextNode->value != valToRem) { // Continue traversing left.
      return remove(nextNode, valToRem);

    } else if (nextNode->value ==
               valToRem) { // Found node to del. BASE CASE: Delete.
      int nodeToRemChildCount = getChildCount(nextNode);

      if (nodeToRemChildCount == 0) { // Leaf case.
        subHead->leftPtr = nullptr;
        subHead->rightThread = nextNode->rightThread;

      } else if (nodeToRemChildCount == 2) { // Double-children case.
        //subHead->leftPtr = remove(nextNode->rightThread, valToRem);
              // find a largest node on left side (so it won't have a right ptr) and
        // make it the head
        Node *largest = subHead->leftPtr;
        Node *largestParent = nullptr;

        while ((largest->rightPtr)) {
          largestParent = largest;
          largest = largest->rightPtr;
        }
        if (largestParent) {
          largestParent->rightPtr = largest->leftPtr;
          largest->leftPtr = subHead->leftPtr;
        }

        largest->rightPtr = subHead->rightPtr;
        largest->rightThread = subHead->rightThread;
        subHead = largest;

      } else {                           // Single child case.
        if (nodeToRemChildCount == -1) { // Single-left child case.
          subHead->leftPtr = nextNode->leftPtr;

        } else if (nodeToRemChildCount == 1) { // Single-right child case.
          subHead->leftPtr = nextNode->rightPtr;
        }
      }

      clearPtrs(nextNode); // Clear removed node's access to tree.
      return nextNode;
    }

  } else { // subhead->value <= valToRem. Look right. ================= RIGHT
    Node *nextNode = subHead->rightPtr;

    if (nextNode == nullptr) {
      return nullptr; // valToDelete DNE in tree. Case: Fail.

    } else if (nextNode->value != valToRem) { // Continue traversing left.
      return remove(nextNode, valToRem);

    } else if (nextNode->value ==
               valToRem) { // Found node to del. BASE CASE: Delete.
      int nodeToRemChildCount = getChildCount(nextNode);

      if (nodeToRemChildCount == 0) { // Leaf case.
        subHead->rightPtr = nullptr;
        subHead->rightThread = nextNode->rightThread;

      } else if (nodeToRemChildCount == 2) { // Double-children case.
        subHead->rightPtr = remove(nextNode->leftThread, valToRem);

      } else {                           // Single child case.
        if (nodeToRemChildCount == -1) { // Single-left child case.
          subHead->rightPtr = nextNode->leftPtr;
          if (nextNode->rightThread == subHead) {
            nextNode->rightThread = subHead->rightThread;
          }

        } else if (nodeToRemChildCount == 1) { // Single-right child case.
          subHead->rightPtr = nextNode->rightPtr;
          subHead->rightThread = nextNode->rightThread;
          if (nextNode->leftThread == subHead) {
            nextNode->leftThread = subHead->leftThread;
          }
        }
      }

      clearPtrs(nextNode); // Clear removed node's access to tree.
      return nextNode;
    }
  }

  return nullptr;
}

/**
 * Sets all pointers of a node (children and threads) to nullptr.
 */
void ThreadedBST::clearPtrs(Node *node) {
  node->leftPtr = nullptr;
  node->rightPtr = nullptr;

  node->leftThread = nullptr;
  node->rightThread = nullptr;
}

/**
 * @returns Number representing number of children.
 *          SPECIAL RETURN FOR SINGLE-LEFT  CHILD.
 *          0 or 2: Number of children.
 *          -1: Single-child (left).
 *           1: Single-child (right).
 */
int ThreadedBST::getChildCount(Node *node) {
  if (node->leftPtr == nullptr && node->rightPtr == nullptr) {
    return 0; // Has no children

  } else {
    if (node->leftPtr == nullptr) { // Has single right child.
      return 1;

    } else if (node->rightPtr == nullptr) { // Has single left child.
      return -1;

    } else { // Has two children.
      return 2;
    }
  }
}

/**
 * Clear function to delete TBST.
 * @note Helper function for destructor.
 */
void ThreadedBST::clear() { clearNodes(headPtr); }

/**
 * Clear function to recusivley delete TBST.
 * @note Helper function for non-recursive clear().
 */
void ThreadedBST::clearNodes(Node *node) {
  if (node == nullptr) {
    return;
  }

  clearNodes(node->leftPtr);
  clearNodes(node->rightPtr);

  delete node;
}

/**
 * @pre If the tree is empty, the headPtr is set to nullptr.
 * @return True if the tree is empty, false if not.
 */
bool ThreadedBST::isEmpty() const { return (headPtr == nullptr); }

/**
 * Iterator for in-order traversal of the tree.
 *
 * @note In-order traversal: Left-root-Right.
 */
std::vector<int> ThreadedBST::inorderTraversal() const {
  std::vector<int> nums;

  // Edge case: Empty list.
  if (headPtr == nullptr) {
    return nums;
  }

  // Start from left-most node.
  Node *currNode = getLeftLeaf(headPtr);

  while (currNode != nullptr) {
    nums.push_back(currNode->value);
    currNode = currNode->rightThread;
  }

  return nums;
}

/**
 * @note   Helper function.
 * @return Node ptr to node that is a parent of node with value childVal.
 *         Return headPtr if the head has the value (fail case),
 *         Return nullptr if tree is empty or no node has childVal (fail
 * case).
 */
Node *ThreadedBST::getParent(int childVal) const {
  // Fail case: Empty tree.
  if (headPtr == nullptr) {
    return nullptr;
  }

  // Fail case: Head pointer has no parent. Return self.
  if (headPtr->value == childVal) {
    return headPtr;
  }

  // Iterate through tree.
  Node *currNode = headPtr;
  while (currNode != nullptr) {
    // Success case: Parent found.
    if ((currNode->leftPtr != nullptr &&
         currNode->leftPtr->value == childVal) ||
        (currNode->rightPtr != nullptr &&
         currNode->rightPtr->value == childVal)) {

      // Traversal
      if (childVal < currNode->value) {
        currNode = currNode->leftPtr;
      } else {
        currNode = currNode->rightPtr;
      }
    }
  }

  return nullptr; // At this point, no node has childVal.
}

/**
 * @note   Helper function.
 * @return Left-most leaf of given node.
 */
Node *ThreadedBST::getLeftLeaf(Node *node) const {
  // Fail case.
  if (node == nullptr) {
    return nullptr;
  }

  while (node->leftPtr != nullptr) {
    node = node->leftPtr;
  }
  return node;
}

/**
 * Left rotation.
 */
Node *ThreadedBST::rightRightBalance(Node *root) {
  Node *newRoot = root->rightPtr;
  root->rightPtr = newRoot->leftPtr;
  newRoot->leftPtr = root;

  getHeight(root);
  return newRoot;
}

/**
 * Right-left rotations.
 */
Node *ThreadedBST::rightLeftBalance(Node *root) {
  Node *newRoot = root->rightPtr->leftPtr;
  Node *oldRight = root->rightPtr;

  oldRight->leftPtr = newRoot->rightPtr;
  newRoot->rightPtr = oldRight;

  root->rightPtr = newRoot->leftPtr;
  newRoot->leftPtr = root;

  getHeight(newRoot);

  return newRoot;
}

/**
 * Right rotation.
 */
Node *ThreadedBST::leftLeftBalance(Node *root) {
  Node *newRoot = root->leftPtr;
  root->leftPtr = newRoot->rightPtr;
  newRoot->rightPtr = root;

  getHeight(root);
  return newRoot;
}

/**
 * Left-right rotations.
 */
Node *ThreadedBST::leftRightBalance(Node *root) {
  Node *newRoot = root->leftPtr->rightPtr;
  Node *oldLeft = root->leftPtr;

  oldLeft->rightPtr = newRoot->leftPtr;
  newRoot->leftPtr = oldLeft;

  root->leftPtr = newRoot->rightPtr;
  newRoot->rightPtr = root;

  getHeight(newRoot);

  return newRoot;
}

/**
 * Updates height and balance factor of nodes.
 *
 * @return Int representing height, where a hieght of a leaf is 1.
 */
int ThreadedBST::getHeight(Node *node) {
  // Base case: leaf height = 1, leaf's child = 0.
  if (node == nullptr) {
    return 0;
  }

  node->height =
      (1 + std::max(getHeight(node->leftPtr), getHeight(node->rightPtr)));

  node->balanceFactor = balanceFactor(node);

  // Add 1 for current node, + the highest height of left/right subtrees.
  return node->height;
}

/**
 *
 */
void ThreadedBST::setTraversals(std::vector<int> &preOrderT,
                                std::vector<int> &inOrderT,
                                std::vector<int> &postOrderT) const {
  preOrderT.clear();
  inOrderT.clear();
  postOrderT.clear();

  traverse(headPtr, preOrderT, inOrderT, postOrderT);
}

/**
 * @note Recusrive helper function.
 */
void ThreadedBST::traverse(Node *node, std::vector<int> &preOrderT,
                           std::vector<int> &inOrderT,
                           std::vector<int> &postOrderT) const {
  if (node == nullptr) {
    return;
  }

  preOrderT.push_back(node->value);

  traverse(node->leftPtr, preOrderT, inOrderT, postOrderT);

  inOrderT.push_back(node->value);

  traverse(node->rightPtr, preOrderT, inOrderT, postOrderT);

  postOrderT.push_back(node->value);
}