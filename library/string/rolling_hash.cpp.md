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
    - Last commit date: 2020-07-11 19:42:18+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <chrono>

template <class Base>
class hash_string {
public:
  using mod_type  = uint64_t;
  using base_type = uint32_t;
  using size_type = size_t;

  static constexpr mod_type mod = (mod_type(1) << 61) - 1;
  static base_type base() { return Base::value(); }

private:
  std::string M_string;
  std::vector<mod_type> M_power, M_hash;

public:
  hash_string() { initialize(); }
  hash_string(const std::string &initial_) { construct(initial_); }

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
      M_power[i + 1] = (__uint128_t) M_power[i] * base() % mod;
      M_hash[i + 1] = ((__uint128_t) M_hash[i] * base() + M_string[i]) % mod;
    }
  }

  mod_type hash(size_type l, size_type r) const {
    return (M_hash[r] + mod - ((__uint128_t) M_power[r - l] * M_hash[l]) % mod) % mod;
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

struct rolling_hash_base {
  static uint32_t &value() {
    static uint32_t base = [] {
      auto time_point = std::chrono::system_clock::now();
      return time_point.time_since_epoch().count();
    }();
    return base;
  }
};
using rolling_hash = hash_string<rolling_hash_base>;

/**
 * @title Rolling Hash
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/rolling_hash.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <chrono>

template <class Base>
class hash_string {
public:
  using mod_type  = uint64_t;
  using base_type = uint32_t;
  using size_type = size_t;

  static constexpr mod_type mod = (mod_type(1) << 61) - 1;
  static base_type base() { return Base::value(); }

private:
  std::string M_string;
  std::vector<mod_type> M_power, M_hash;

public:
  hash_string() { initialize(); }
  hash_string(const std::string &initial_) { construct(initial_); }

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
      M_power[i + 1] = (__uint128_t) M_power[i] * base() % mod;
      M_hash[i + 1] = ((__uint128_t) M_hash[i] * base() + M_string[i]) % mod;
    }
  }

  mod_type hash(size_type l, size_type r) const {
    return (M_hash[r] + mod - ((__uint128_t) M_power[r - l] * M_hash[l]) % mod) % mod;
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

struct rolling_hash_base {
  static uint32_t &value() {
    static uint32_t base = [] {
      auto time_point = std::chrono::system_clock::now();
      return time_point.time_since_epoch().count();
    }();
    return base;
  }
};
using rolling_hash = hash_string<rolling_hash_base>;

/**
 * @title Rolling Hash
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

