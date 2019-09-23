#include "pch.h"
#include "..//Data Structure/DoubleLinkedList.hh"
#include <stdexcept>

TEST(DoubleLinkedListTest, InitTest) {
  AYJ::DoubleLinkedList<int> list;
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(DoubleLinkedListTest, FrontTest) {
  AYJ::DoubleLinkedList<int> list;
  list.push_front(10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.front(), 10);
  list.push_front(20);
  EXPECT_EQ(list.front(), 20);
  list.pop_front();
  EXPECT_EQ(list.front(), 10);
}

TEST(DoubleLinkedListTest, BackTest) {
  AYJ::DoubleLinkedList<int> list;
  list.push_back(10);
  EXPECT_EQ(list.back(), 10);
  list.push_back(20);
  EXPECT_EQ(list.back(), 20);
  list.pop_back();
  EXPECT_EQ(list.back(), 10);
  list.pop_back();
  EXPECT_TRUE(list.empty());
  try {
    list.pop_back();
    EXPECT_ANY_THROW(0);
  } catch(std::exception& e) {}
}

TEST(DoubleLinkedListTest, IteratorTest) {
  AYJ::DoubleLinkedList<int> list;
  list.push_back(10);
  list.push_front(20);
  list.push_back(10);
  list.push_front(20);
  EXPECT_EQ(list.size(), 4);
  AYJ::DoubleLinkedList<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_EQ(*it, 10);
  it++;
  EXPECT_EQ(*it, 10);
  it++;
  EXPECT_TRUE(it==list.end());
  try {
    it++;
    EXPECT_ANY_THROW(0);
  } catch (std::exception& e) {
  }
}

TEST(DoubleLinkedListTest, InsertTest) {
  AYJ::DoubleLinkedList<int> list;
  list.push_back(10);
  AYJ::DoubleLinkedList<int>::iterator it = list.begin();
  list.insert(it, 20);
  EXPECT_EQ(*it, 10);
  it++;
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_TRUE(it == list.end());
}

TEST(DoubleLinkedListTest, RemoveTest) {
  AYJ::DoubleLinkedList<int> list;
  list.push_back(10);
  list.push_back(20);
  AYJ::DoubleLinkedList<int>::iterator it = list.begin();
  it = list.remove(it);
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_TRUE(it == list.end());
}