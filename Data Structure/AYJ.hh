#ifndef AYJ_H
#define AYJ_H

namespace AYJ {
using size_type=unsigned int;

template <class T>
struct less {
  bool operator()(const T& a, const T& b) const {
    return a < b;
  }
};

template <class T>
struct greater {
  bool operator()(const T& a, const T& b) const {
    return a > b;
  }
};

}
#endif