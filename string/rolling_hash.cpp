#pragma once

#include "../other/random_number.cpp"

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <chrono>

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
    return op_t::sub(M_hash[r], op_t::mul(op_t::power(r - l), M_hash[l]));
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
    M_hash.clear();
    M_hash.shrink_to_fit();
  }

};

/**
 * @title Rolling Hash
 */