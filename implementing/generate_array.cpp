
#include "../other/random_number.cpp"

#include <cstddef>
#include <random>
#include <algorithm>
#include <vector>

template <class RandomAccessIterator>
void shuffle(RandomAccessIterator first, RandomAccessIterator last) {
  static std::default_random_engine gen(engine());
  std::shuffle(first, last, gen);
}

template <class T>
std::vector<T> fixed_range_array(const size_t size, const T lower, const T upper) {
  std::vector<T> res(size);
  for (auto &x: res) {
    x = random_number(lower, upper);
  }
  return res;
}

template <class T>
std::vector<T> fixed_sum_array(const size_t size, const T sum) {
  auto vec = fixed_range_array(size - 1, T(0), sum);
  vec.push_back(T(0));
  vec.push_back(sum);
  std::sort(vec.begin(), vec.end());
  std::vector<T> res(size);
  for (size_t i = 0; i < size; ++i) {
    res[i] = vec[i + 1] - vec[i];
  }
  return res;
}

std::vector<size_t> random_permutation(const size_t size) {
  std::vector<size_t> res(size);
  std::iota(res.begin(), res.end(), 0);
  shuffle(res.begin(), res.end());
  return res;
}

/**
 * @title Random Array Generator
 */