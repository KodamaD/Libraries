---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: Rolling Hash

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/rolling_hash.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 18:08:09+09:00




## Depends on

* :warning: <a href="../other/random_number.cpp.html">Random Number</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../other/random_number.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <cassert>

namespace rolling_hash_detail {

class hash61_t {
public:

  static constexpr uint64_t mod() {
    return (static_cast<uint64_t>(1) << 61) - 1;
  }
  static uint32_t base() {
    static const uint32_t value = static_cast<uint32_t>(engine());
    return value;
  }

  static constexpr uint64_t add(uint64_t a, uint64_t b) {
    a += b;
    if (a >= mod()) a -= mod();
    return a;
  }
  static constexpr uint64_t sub(uint64_t a, uint64_t b) {
    a += mod() - b;
    if (a >= mod()) a -= mod();
    return a;
  }
  static constexpr uint64_t mul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t res = (l & mod()) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    res = (res & mod()) + (res >> 61);
    res = (res & mod()) + (res >> 61);
    return res - 1;
  }

  static std::vector<uint64_t> reserve;
  static uint64_t power(const size_t index) {
    if (index >= reserve.size()) {
      size_t cur = reserve.size();
      reserve.resize(index + 1);
      for (; cur <= index; ++cur) {
        reserve[cur] = mul(reserve[cur - 1], base());
      }
    }
    return reserve[index];
  }

};

std::vector<uint64_t> hash61_t::reserve = std::vector<uint64_t>(1, 1);

};

class rolling_hash {
public:
  using hash_type = uint64_t;
  using size_type = size_t;

private:
  using op_t = rolling_hash_detail::hash61_t;

  std::string M_string;
  std::vector<hash_type> M_hash;

public:
  rolling_hash() { initialize(); }
  rolling_hash(const std::string &initial_) { construct(initial_); }

  void initialize() {
    clear();
    M_string = "";
    M_hash.assign(1, 0);
  }
  void construct(const std::string &initial_) {
    initialize();
    add_string(initial_);
  }

  void add_string(const std::string &str) {
    size_type cur_size = M_string.size();
    size_type next_size = M_string.size() + str.size();
    M_string += str;
    M_hash.resize(next_size + 1);
    for (size_type i = cur_size; i < next_size; ++i) {
      M_hash[i + 1] = op_t::add(op_t::mul(M_hash[i], op_t::base()), M_string[i]);
    }
  }

  hash_type hash(size_type l, size_type r) const {
    assert(l <= r);
    assert(r <= size());
    return op_t::sub(M_hash[r], op_t::mul(op_t::power(r - l), M_hash[l]));
  }
  size_type lcp(size_type l, size_type r) const {
    assert(l < size());
    assert(r < size());
    size_type ok = 0, ng = std::min(M_string.size() - l, M_string.size() - r) + 1;
    while (ng - ok > 1) {
      size_type md = (ok + ng) >> 1;
      (hash(l, l + md) == hash(r, r + md) ? ok : ng) = md;
    }
    return ok;
  }

  const std::string &get() const {
    return M_string;
  }
  size_type size() const {
    return M_string.size();
  }
  bool empty() const {
    return M_string.empty();
  }
  void clear() {
    M_string.clear();
    M_string.shrink_to_fit();
    M_hash.clear();
    M_hash.shrink_to_fit();
  }
};

/**
 * @title Rolling Hash
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/rolling_hash.cpp"

#line 2 "other/random_number.cpp"

#include <cstdint>
#include <random>
#include <chrono>
#include <array>
#include <type_traits>

uint64_t engine() {
  static const auto rotate = [](const uint64_t x, const size_t k) {
    return (x << k) | (x >> (64 - k));
  };
  static auto array = [] {
    uint64_t seed = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());
    std::array<uint64_t, 4> res{};
    for (size_t index = 0; index < 4; index++) {
      uint64_t value = (seed += 0x9e3779b97f4a7c15);
      value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9;
      value = (value ^ (value >> 27)) * 0x94d049bb133111eb;
      res[index] = value ^ (value >> 31);
    }
    return res;
  }();
  const uint64_t result = rotate(array[1] * 5, 7) * 9;
  const uint64_t old_value = array[1] << 17;
  array[2] ^= array[0];
  array[3] ^= array[1];
  array[1] ^= array[2];
  array[0] ^= array[3];
  array[2] ^= old_value;
  array[3] = rotate(array[3], 45);
  return result;
}

template <class Integer>
typename std::enable_if<std::is_integral<Integer>::value, Integer>::type random_number(Integer lower, Integer upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_int_distribution<Integer>(lower, upper)(gen);
}

template <class Real>
typename std::enable_if<!std::is_integral<Real>::value, Real>::type random_number(Real lower, Real upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_real_distribution<Real>(lower, upper)(gen);
}

/** 
 * @title Random Number
 */
#line 4 "string/rolling_hash.cpp"

#include <cstddef>
#line 7 "string/rolling_hash.cpp"
#include <vector>
#include <string>
#include <cassert>

namespace rolling_hash_detail {

class hash61_t {
public:

  static constexpr uint64_t mod() {
    return (static_cast<uint64_t>(1) << 61) - 1;
  }
  static uint32_t base() {
    static const uint32_t value = static_cast<uint32_t>(engine());
    return value;
  }

  static constexpr uint64_t add(uint64_t a, uint64_t b) {
    a += b;
    if (a >= mod()) a -= mod();
    return a;
  }
  static constexpr uint64_t sub(uint64_t a, uint64_t b) {
    a += mod() - b;
    if (a >= mod()) a -= mod();
    return a;
  }
  static constexpr uint64_t mul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t res = (l & mod()) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    res = (res & mod()) + (res >> 61);
    res = (res & mod()) + (res >> 61);
    return res - 1;
  }

  static std::vector<uint64_t> reserve;
  static uint64_t power(const size_t index) {
    if (index >= reserve.size()) {
      size_t cur = reserve.size();
      reserve.resize(index + 1);
      for (; cur <= index; ++cur) {
        reserve[cur] = mul(reserve[cur - 1], base());
      }
    }
    return reserve[index];
  }

};

std::vector<uint64_t> hash61_t::reserve = std::vector<uint64_t>(1, 1);

};

class rolling_hash {
public:
  using hash_type = uint64_t;
  using size_type = size_t;

private:
  using op_t = rolling_hash_detail::hash61_t;

  std::string M_string;
  std::vector<hash_type> M_hash;

public:
  rolling_hash() { initialize(); }
  rolling_hash(const std::string &initial_) { construct(initial_); }

  void initialize() {
    clear();
    M_string = "";
    M_hash.assign(1, 0);
  }
  void construct(const std::string &initial_) {
    initialize();
    add_string(initial_);
  }

  void add_string(const std::string &str) {
    size_type cur_size = M_string.size();
    size_type next_size = M_string.size() + str.size();
    M_string += str;
    M_hash.resize(next_size + 1);
    for (size_type i = cur_size; i < next_size; ++i) {
      M_hash[i + 1] = op_t::add(op_t::mul(M_hash[i], op_t::base()), M_string[i]);
    }
  }

  hash_type hash(size_type l, size_type r) const {
    assert(l <= r);
    assert(r <= size());
    return op_t::sub(M_hash[r], op_t::mul(op_t::power(r - l), M_hash[l]));
  }
  size_type lcp(size_type l, size_type r) const {
    assert(l < size());
    assert(r < size());
    size_type ok = 0, ng = std::min(M_string.size() - l, M_string.size() - r) + 1;
    while (ng - ok > 1) {
      size_type md = (ok + ng) >> 1;
      (hash(l, l + md) == hash(r, r + md) ? ok : ng) = md;
    }
    return ok;
  }

  const std::string &get() const {
    return M_string;
  }
  size_type size() const {
    return M_string.size();
  }
  bool empty() const {
    return M_string.empty();
  }
  void clear() {
    M_string.clear();
    M_string.shrink_to_fit();
    M_hash.clear();
    M_hash.shrink_to_fit();
  }
};

/**
 * @title Rolling Hash
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

