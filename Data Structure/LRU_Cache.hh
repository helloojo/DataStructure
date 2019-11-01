#ifndef AYJ_LRU_CACHE_HH
#define AYJ_LRU_CACHE_HH
#include "DoubleLinkedList.hh"
namespace AYJ {
/*
Key, Value ±â¹Ý LRU Cache
*/
template<class Key_, class Value_>
class LRUCache {
public:
  LRUCache() : max_size_(default_size) {}
  LRUCache(size_type max_size) : max_size_(max_size) {}
  Value_& get(const Key_& key) {
    auto find_result = find(key);
    if (find_result == cache_.end()) {
      return find_result->value;
    }
    cache_.push_front(*find_result);
    cache_.remove(find_result);
    return top();
  }
  void put(const Key_& key, const Value_& value) {
    cache_.push_front({ key,value });
    if (cache_.size() == max_size_ + 1) {
      cache_.pop_back();
    }
  }
  Value_& top() {
    return cache_.front().value;
  }
  size_type max_size() const {
    return max_size_;
  }
  size_type size() const {
    return cache_.size();
  }
  bool empty() const {
    return cache_.empty();
  }
private:
  const static size_type default_size = 30;
  const size_type max_size_;
  struct Data {
    Key_ key;
    Value_ value;
  };
  DoubleLinkedList<Data> cache_;
  typename DoubleLinkedList<Data>::iterator find(const Key_& key) {
    auto end = cache_.end();
    for (auto it = cache_.begin(); it != end; ++it) {
      if (it->key == key) {
        return it;
      }
    }
    return end;
  }
};

}

#endif