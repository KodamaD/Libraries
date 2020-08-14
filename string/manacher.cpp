#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iterator>

template <class InputIterator>
class manacher_impl {
public:
  using value_type = typename InputIterator::value_type;

public:
  std::vector<size_t> odd, even;

  explicit manacher_impl(InputIterator first, InputIterator last, const value_type &never) {
    const size_t size = std::distance(first, last);
    odd.resize(size);
    even.resize(size - 1);
    std::vector<value_type> str;
    str.reserve(2 * size + 1);
    for (; first != last; ++first) {
      str.push_back(never);
      str.push_back(*first);
    }
    str.push_back(never);
    std::vector<int32_t> calc(str.size());
    int32_t i = 0, j = 0;
    while (i < (int32_t) str.size()) {
      while (i - j >= 0 && i + j < (int32_t) str.size() && str[i - j] == str[i + j]) {
        ++j;
      }
      calc[i] = j;
      int32_t k = 1;
      while (i - k >= 0 && k + calc[i - k] < j) {
        calc[i + k] = calc[i - k];
        ++k;
      }
      i += k;
      j -= k;
    }
    for (size_t k = 1; k + 1 < str.size(); ++k) {
      if (k % 2 == 1) {
        odd[k / 2] = calc[k] - 1;
      }
      else {
        even[k / 2 - 1] = calc[k] - 1;
      }
    }
  }

};

template <class InputIterator>
manacher_impl<InputIterator> manacher(InputIterator first, InputIterator last, const typename InputIterator::value_type &never) {
  return manacher_impl<InputIterator>(first, last, never);
}

/**
 * @title Manacher
 */