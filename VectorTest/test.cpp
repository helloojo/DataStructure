#include "pch.h"
#include "..//Data Structure/Vector.hh"
#include <stdexcept>

TEST(VectorTest, InitTest) {
  AYJ::Vector<int> vector;
  EXPECT_EQ(vector.size(), 0);
  EXPECT_EQ(vector.capacity(), 15);
  EXPECT_TRUE(vector.empty());
  AYJ::Vector<int> vector2(10);
  EXPECT_EQ(vector2.size(), 10);
  EXPECT_EQ(vector2.capacity(), 10);
}

TEST(VectorTest, PushAndIndexTest) {
  AYJ::Vector<int> vector;
  vector.push_back(0);
  vector.push_back(10);
  vector.push_back(20);
  vector.push_back(30);
  vector.push_back(40);
  vector.push_back(50);
  for (int i = 0; i < vector.size(); i++) {
    EXPECT_EQ(i * 10, vector.at(i));
    EXPECT_EQ(i * 10, vector[i]);
  }
}

TEST(VectorTest, PopTest) {
  AYJ::Vector<int> vector;
  vector.push_back(10);
  EXPECT_EQ(vector.back(), 10);
  EXPECT_EQ(vector.size(), 1);
  vector.pop_back();
  EXPECT_EQ(vector.size(), 0);
  EXPECT_TRUE(vector.empty());
}

TEST(VectorTest, AssignTest) {
  AYJ::Vector<int> vector;
  vector.assign(10, 10);
  EXPECT_EQ(vector.back(), 10);
  EXPECT_EQ(vector.size(), 10);
}

TEST(VectorTest, ReserveTest) {
  AYJ::Vector<int> vector;
  vector.reserve(10);
  EXPECT_NE(vector.capacity(), 10);
  vector.reserve(30);
  EXPECT_EQ(vector.capacity(), 30);
}

TEST(VectorTest, IteratorTest) {
  AYJ::Vector<int> vector;
  for (int i = 0; i < 5; i++) {
    vector.push_back(i);
  }
  int ii = 0;
  for (auto it = vector.begin(); it != vector.end(); it++) {
    EXPECT_EQ(*it, ii++);
  }
  AYJ::Vector<int>::iterator it = vector.begin();
  EXPECT_EQ(vector.front(), 0);
  EXPECT_EQ(*it, 0);
  *it = 10;
  EXPECT_EQ(vector.front(), 10);
  it += 2;
  EXPECT_EQ(*it, 2);
  it -= 2;
  EXPECT_EQ(*it, 10);
}