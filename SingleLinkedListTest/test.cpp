#include "pch.h"
#include "../Data Structure/SingleLinkedList.hh"
#include <stdexcept>

TEST(SingleLinkedListTest, InitTest) {
  AYJ::SingleLinkedList<int> list;
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(SingleLinkedListTest, PushTest) {
  AYJ::SingleLinkedList<int> list;
  list.push_front(3);
  list.push_front(2);
  list.push_front(1);
  EXPECT_EQ(list.size(), 3);
  int i = 1;
  for (auto it = list.begin(); it != list.end(); it++) {
    EXPECT_EQ(*it, i++);
  }
}

TEST(SingleLinkedListTest, FrontTest) {
  AYJ::SingleLinkedList<int> list;
  list.push_front(10);
  EXPECT_EQ(list.front(), 10);
  list.push_front(20);
  EXPECT_EQ(list.front(), 20);
}

TEST(SingleLinkedListTest, PopTest) {
  AYJ::SingleLinkedList<int> list;
  list.push_front(10);
  EXPECT_EQ(list.size(), 1);
  list.pop_front();
  EXPECT_TRUE(list.empty());
  try {
    list.pop_front();
    EXPECT_ANY_THROW(0);
  } catch (std::exception& e) {
  }
}

TEST(SingleLinkedListTest, IteratorTest) {
  AYJ::SingleLinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  AYJ::SingleLinkedList<int>::iterator it = list.begin();
  int i = 4;
  while (i) {
    EXPECT_EQ(*it, i--);
    it++;
  }
  try {
    it++;
    EXPECT_ANY_THROW(0);
  } catch (std::exception& e) {
  }
  it = list.begin();
  EXPECT_TRUE(list.begin() == it);
  struct data {
    int d;
  };
  AYJ::SingleLinkedList<data> data_list;
  data_list.push_front({ 1 });
  auto iter = data_list.begin();

  EXPECT_EQ((*iter).d, 1);
  EXPECT_EQ(iter->d, 1);
}