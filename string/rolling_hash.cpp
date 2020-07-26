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