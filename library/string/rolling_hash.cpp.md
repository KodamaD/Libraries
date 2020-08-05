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
    - Last commit date: 2020-08-05 18:30:10+09:00




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
#include <chrono>

class rolling_hash {
public:
  using mod_type  = uint64_t;
  using base_type = uint32_t;
  using size_type = size_t;

private:
  std::string M_string;
  std::vector<mod_type> M_power, M_hash;

  static constexpr mod_type S_mod = (mod_type(1) << 61) - 1;
  static base_type S_base() { 
    static const base_type value = engine();
    return value;
  }

public:
  rolling_hash() { initialize(); }
  rolling_hash(const std::string &initial_) { construct(initial_); }

  void initialize() {
    clear();
    M_string = "";
    M_power.assign(1, 1);
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
    M_power.resize(next_size + 1);
    M_hash.resize(next_size + 1);
    for (size_type i = cur_size; i < next_size; ++i) {
      M_power[i + 1] = (__uint128_t) M_power[i] * S_base() % S_mod;
      M_hash[i + 1] = ((__uint128_t) M_hash[i] * S_base() + M_string[i]) % S_mod;
    }
  }

  mod_type hash(size_type l, size_type r) const {
    return (M_hash[r] + S_mod - ((__uint128_t) M_power[r - l] * M_hash[l]) % S_mod) % S_mod;
  }
  size_type lcp(size_type l, size_type r) const {
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
    M_power.clear();
    M_power.shrink_to_fit();
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
Integer random_integer(Integer lower, Integer upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_int_distribution<Integer>(lower, upper)(gen);
}

template <class Real>
Real random_real(Real lower, Real upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_real_distribution<Real>(lower, upper)(gen);
}

/** 
 * @title Random Number
 */
#line 4 "string/rolling_hash.cpp"
#include <cstddef>
#line 6 "string/rolling_hash.cpp"
#include <vector>
#include <string>
#line 9 "string/rolling_hash.cpp"

class rolling_hash {
public:
  using mod_type  = uint64_t;
  using base_type = uint32_t;
  using size_type = size_t;

private:
  std::string M_string;
  std::vector<mod_type> M_power, M_hash;

  static constexpr mod_type S_mod = (mod_type(1) << 61) - 1;
  static base_type S_base() { 
    static const base_type value = engine();
    return value;
  }

public:
  rolling_hash() { initialize(); }
  rolling_hash(const std::string &initial_) { construct(initial_); }

  void initialize() {
    clear();
    M_string = "";
    M_power.assign(1, 1);
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
    M_power.resize(next_size + 1);
    M_hash.resize(next_size + 1);
    for (size_type i = cur_size; i < next_size; ++i) {
      M_power[i + 1] = (__uint128_t) M_power[i] * S_base() % S_mod;
      M_hash[i + 1] = ((__uint128_t) M_hash[i] * S_base() + M_string[i]) % S_mod;
    }
  }

  mod_type hash(size_type l, size_type r) const {
    return (M_hash[r] + S_mod - ((__uint128_t) M_power[r - l] * M_hash[l]) % S_mod) % S_mod;
  }
  size_type lcp(size_type l, size_type r) const {
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
    M_power.clear();
    M_power.shrink_to_fit();
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

