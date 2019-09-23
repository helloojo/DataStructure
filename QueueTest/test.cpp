#include "pch.h"
#include "..//Data Structure/Queue.hh"

TEST(QueueTest, QueueTest) {
  AYJ::Queue<int, AYJ::DoubleLinkedList<int>> st;
  st.push(10);
  EXPECT_EQ(st.size(), 1);
  EXPECT_EQ(st.front(), 10);
  st.push(20);
  EXPECT_EQ(st.front(), 10);
  st.pop();
  EXPECT_EQ(st.front(), 20);
  st.pop();
  EXPECT_TRUE(st.empty());
}