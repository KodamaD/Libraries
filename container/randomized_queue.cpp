#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>
#include <algorithm>

template <class T>
class randomized_queue {
public:
  using value_type = T;
  using size_type = size_t;

  static uint64_t engine() {
    static uint64_t current = 7511168;
    current ^= (current << 9);
    current ^= (current >> 7);
    return current;
  }
  
private:
  std::vector<value_type> M_data;

public:
  randomized_queue() = default;
  template <class InputIterator>
  explicit randomized_queue(InputIterator first, InputIterator last) { construct(first, last); }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) { 
    clear();
    const size_type size = std::distance(first, last);
    M_data.reserve(size);
    std::copy(first, last, std::back_inserter(M_data));
  }

  void shuffle() {
    std::swap(M_data.back(), M_data[engine() % M_data.size()]);
  }

  value_type front() const {
    return M_data.back();
  }
  bool empty() const {
    return M_data.empty();
  }
  size_type size() const {
    return M_data.size();
  }

  void push(const value_type &val) {
    M_data.push_back(val);
    shuffle();
  }
  void pop() {
    M_data.pop_back();
    if (!M_data.empty()) {
      shuffle();
    }
  }
  void clear() {
    M_data.clear();
    M_data.shrink_to_fit();
  }

};
