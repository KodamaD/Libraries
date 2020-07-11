#pragma once

#include <cstddef>
#include <vector>
#include <numeric>
#include <algorithm>

template <class T>
class suffix_array {
public:
  using value_type = T;
  using size_type  = size_t;

private:
  std::vector<value_type> M_data;
  std::vector<size_type> M_array, M_rank;

public:
  suffix_array() = default;
  template <class InputIterator>
  explicit suffix_array(InputIterator first, InputIterator last) { construct(first, last); } 

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) { 
    clear();
    M_data = std::vector<typename InputIterator::value_type>(first, last);
    M_array.assign(size() + 1, 0);
    M_rank.assign(size() + 1, 0);
    M_array.front() = size();
    std::iota(M_array.begin() + 1, M_array.end(), 0);
    std::stable_sort(M_array.begin() + 1, M_array.end(), [&](size_type i, size_type j) {
      return M_data[i] < M_data[j];
    });
    M_rank[M_array[0]] = 1;
    for (size_type i = 1; i <= size(); ++i) {
      if (i > 1 && M_data[M_array[i]] == M_data[M_array[i - 1]]) M_rank[M_array[i]] = M_rank[M_array[i - 1]];
      else M_rank[M_array[i]] = M_rank[M_array[i - 1]] + 1;
    }
    size_type length;
    auto compare = [&](size_type i, size_type j) {
      if (M_rank[i] != M_rank[j]) return M_rank[i] < M_rank[j];
      size_type ti = (i + length <= size() ? M_rank[i + length] : 0);
      size_type tj = (j + length <= size() ? M_rank[j + length] : 0);
      return ti < tj;
    };
    std::vector<size_type> copy(size() + 1);
    for (length = 1; length < size(); length <<= 1) {
      std::stable_sort(M_array.begin(), M_array.end(), compare);
      copy[M_array[0]] = 1;
      for (size_type i = 1; i <= size(); ++i) {
        copy[M_array[i]] = copy[M_array[i - 1]] + (compare(M_array[i - 1], M_array[i]) ? 1 : 0);
      }
      std::copy(copy.begin(), copy.end(), M_rank.begin());
    }
  }

  size_type operator [](size_type i) const {
    return M_array[i];
  }
  size_type rank(size_type i) const {
    return M_rank[i];
  }

  std::vector<value_type> &get() const {
    return M_data;
  }
  size_type size() const {
    return M_data.size();
  }
  void clear() {
    M_data.clear();
    M_data.shrink_to_fit();
    M_array.clear();
    M_array.shrink_to_fit();
    M_rank.clear();
    M_rank.shrink_to_fit();
  }

};

/**
 * @title Suffix Array
 */