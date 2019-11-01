#include "pch.h"
#include "../Data Structure/LRU_Cache.hh"
TEST(LRU_CacheTest, PutTest) {
  AYJ::LRUCache<int, int> lru_cache(5);
  for (int i = 1; i <= 5; i++) {
    lru_cache.put(i, i);
  }
  EXPECT_EQ(lru_cache.size(), 5);
  EXPECT_EQ(lru_cache.top(), 5);
}

TEST(LRU_CacheTest, GetTest) {
  AYJ::LRUCache<int, int> lru_cache(5);
  for (int i = 1; i <= 5; i++) {
    lru_cache.put(i, i);
  }
  EXPECT_EQ(lru_cache.get(1), 1);
  EXPECT_EQ(lru_cache.top(), 1);
  EXPECT_EQ(lru_cache.get(3), 3);
  EXPECT_EQ(lru_cache.top(), 3);
}