#include "pch.h"
#include "..//Data Structure/Stack.hh"
#include "..//Data Structure/DoubleLinkedList.hh"


TEST(StackTest, VectorStackTest) {
  AYJ::Stack<int, AYJ::Vector<int>> st;
  st.push(10);
  EXPECT_EQ(st.size(), 1);
  EXPECT_EQ(st.top(), 10);
  st.push(20);
  EXPECT_EQ(st.top(), 20);
  st.pop();
  EXPECT_EQ(st.top(), 10);
  st.pop();
  EXPECT_TRUE(st.empty());
}

TEST(StackTest, ListStackTest) {
  AYJ::Stack<int, AYJ::DoubleLinkedList<int>> st;
  st.push(10);
  EXPECT_EQ(st.size(), 1);
  EXPECT_EQ(st.top(), 10);
  st.push(20);
  EXPECT_EQ(st.top(), 20);
  st.pop();
  EXPECT_EQ(st.top(), 10);
  st.pop();
  EXPECT_TRUE(st.empty());
}