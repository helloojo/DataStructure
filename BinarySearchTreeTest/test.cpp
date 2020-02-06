#include "pch.h"
#include "..//Data Structure/BinarySearchTree.hh"

TEST(BinarySearchTreeTest, ForwardIteratorTest) {
  AYJ::BinarySearchTree<int> tree;
  for (int i = 10; i > 0; i--) {
    tree.insert(i);
  }
  for (int i = 11; i < 20; i++) {
    tree.insert(i);
  }
  int t = 1;
  for (auto it = tree.begin(); it != tree.end(); it++) {
    EXPECT_EQ(t++, *it);
  }
}