#pragma once

#include <vector>
#include <cstddef>
#include <cassert>
#include <algorithm>

template <class T>
class compressor {
  std::vector<T> data;
  bool compressed;

public:
  compressor(const std::size_t capacity = 0) {
    data.reserve(capacity);
    compressed = false;
  }

  void add(const T &value) {
    assert(!compressed);
    data.push_back(value);
  }

  void build() {
    assert(!compressed);
    std::sort(data.begin(), data.end());
    data.erase(std::unique(data.begin(), data.end()), data.end());
    compressed = true;
  }

  std::size_t get(const T &value) const {
    assert(compressed);
    return std::lower_bound(data.cbegin(), data.cend(), value) - data.cbegin();
  }

  std::size_t size() const {
    assert(compressed);
    return data.size();
  }

  T restore(const std::size_t index) const {
    assert(compressed);
    return data[index];
  }
};

/**
 * @title Compressor
 */