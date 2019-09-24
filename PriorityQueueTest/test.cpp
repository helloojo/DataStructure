#include "pch.h"
#include "..//Data Structure/PriorityQueue.hh"

TEST(PriorityQueueTest, InitTest) {
  AYJ::PriorityQueue<int> pq;
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(pq.size(), 0);
}

TEST(PriorityQueueTest, LessPushPopTest) {
  AYJ::PriorityQueue<int> pq;
  for (int i = 0; i <= 1000000; i++) {
    pq.push(i);
  }
  for (int i = 1000000; i >= 0; i--) {
    EXPECT_EQ(i, pq.top());
    pq.pop();
  }
}

TEST(PriorityQueueTest, GreaterPushPopTest) {
  AYJ::PriorityQueue<int, AYJ::Vector<int>, AYJ::greater<int>> pq;
  for (int i = 1000000; i >= 0; i--) {
    pq.push(i);
  }
  for (int i = 0; i <= 1000000; i++) {
    EXPECT_EQ(i, pq.top());
    pq.pop();
  }
}