#include "threadedBST.h"
#include <iostream>

using namespace std;

/**
 * Test constructor, copy constructor, node removal, and output
 * with a tree of size 1.
 */
void test1() {
  int n = 1;
  ThreadedBST origTree(n);
  ThreadedBST newTree = origTree;

  // Remove all evens from newTree (copy).
  for (int i = 2; i < n + 1; i += 2) {
    newTree.remove(i);
  }

  // Output (to compare before/after deletions).
  cout << "Original Tree: " << origTree << endl;
  cout << "New Tree: " << newTree << endl << endl;
}

/**
 * Test constructor, copy constructor, node removal, and output
 * with a tree of size 4.
 */
void test2() {
  int n = 4;
  ThreadedBST origTree(n);
  ThreadedBST newTree = origTree;

  // Remove all evens from newTree (copy).
  for (int i = 2; i < n + 1; i += 2) {
    newTree.remove(i);
  }

  // Output (to compare before/after deletions).
  cout << "Original Tree: " << origTree << endl;
  cout << "New Tree: " << newTree << endl << endl;
}

/**
 * MAIN
 * Run all tests.
 */
int main() {
  test1();
  test2();

  return 0;
}
