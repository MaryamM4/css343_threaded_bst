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

  std::cout << std::endl;
  // Remove all evens from newTree (copy).
  for (int i = 2; i < n + 1; i += 2) {
    std::cout << "remove(" << i << ")" << std::endl;
    newTree.remove(i);
  }

  // Output (to compare before/after deletions).
  cout << "\nOriginal Tree: \n" << origTree << endl;
  cout << "New Tree: \n" << newTree << endl << endl;
}

/**
 * Test constructor, copy constructor, node removal, and output
 * with a tree of size 4.
 */
void test2() {
  int n = 8;
  ThreadedBST origTree(n);
  ThreadedBST newTree = origTree;

  std::cout << std::endl;
  // Remove all evens from newTree (copy).
  for (int i = 2; i < n + 1; i += 2) {
    std::cout << "remove(" << i << ")" << std::endl;
    newTree.remove(i);
  }

  // Output (to compare before/after deletions).
  cout << "\nOriginal Tree: \n" << origTree << endl;
  cout << "New Tree: \n" << newTree << endl << endl;
}

/**
 * Style helper. Prints:
 * <empty line>
 * <line>
 * <str>
 * <line>
 */
void printHeader(std::string str, std::string line) {
  std::cout << "\n" << line << "\n" << str << "\n" << line << std::endl;
}

/**
 * MAIN
 * Run all tests.
 */
int main() {
  printHeader("TEST 1", "================");
  test1();

  printHeader("TEST 2", "================");
  test2();

  return 0;
}
