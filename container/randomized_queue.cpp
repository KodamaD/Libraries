#pragma once

#include "../other/random_number.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>

template <class T>
class randomized_queue {
public:
  using value_type = T;
  using size_type = size_t;

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
    assert(!empty());
    std::swap(M_data.back(), M_data[random_number<size_type>(0, M_data.size() - 1)]);
  }

  value_type front() const {
    assert(!empty());
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
    assert(!empty());
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

/**
 * @title Randomized Queue
 */