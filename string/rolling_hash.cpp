#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <ctime>

template <class Base>
class hash_string {
public:
  using mod_type = uint64_t;
  using base_type = uint32_t;
  using size_type = size_t;
  static constexpr mod_type mod = (mod_type(1) << 61) - 1;
  static base_type base() { return Base::value; }

private:
  std::string M_string;
  std::vector<mod_type> M_power, M_hash;

public:
  hash_string() { initialize(); }
  hash_string(const std::string &initial_) { construct(initial_);}

  void initialize() {
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

  size_type size() const {
    return M_string.size();
  }
  bool empty() const {
    return M_string.empty();
  }
  const std::string &get() const {
    return M_string;
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

};

struct rolling_hash_base { static inline const uint32_t value = std::clock() ^ std::time(nullptr); };
using rolling_hash = hash_string<rolling_hash_base>;
