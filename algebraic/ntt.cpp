#pragma once

#include "../other/bit_operation.cpp"

#include <cstddef>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

namespace ntt_detail {

  constexpr uint32_t primitive_root(const uint32_t mod) {
    std::array<uint32_t, 32> exp{};
    uint32_t cur = mod - 1;
    size_t size = 0;
    for (uint32_t i = 2; i * i <= cur; ++i) {
      if (cur % i == 0) {
        exp[size++] = (mod - 1) / i;
        while (cur % i == 0) cur /= i;
      }
    }
    if (cur != 1) exp[size++] = (mod - 1) / cur;
    for (uint32_t check = 1; check < mod; ++check) {
      for (auto e: exp) {
        if (e == 0) return check;
        uint64_t a = check, x = 1;
        while (e > 0) {
          if (e & 1) (x *= a) %= mod;
          (a *= a) %= mod;
          e >>= 1;
        }
        if (x == 1) break;
      }
    }
    return mod;
  };

  template <size_t N, class T>
  constexpr std::array<T, N> compute_roots(T omega) {
    std::array<T, N> res;
    res[N - 1] = omega;
    for (size_t i = N - 1; i > 0; --i) {
      res[i - 1] = res[i] * res[i];
    }
    return res;
  }

}

template <class Modular>
class number_theoretic_transform {
public:
  using value_type = Modular;
  static constexpr uint32_t mod = Modular::mod();
  static constexpr uint32_t prim = ntt_detail::primitive_root(mod);

private:
  static constexpr size_t level = bit_ctzr(mod - 1);
  static constexpr value_type omega = power(value_type(prim), ((mod - 1) >> level)); 
  static constexpr auto roots = ntt_detail::compute_roots<level>(omega);
  static constexpr auto inv_roots = ntt_detail::compute_roots<level>(inverse(omega));

public:
  static void transform(std::vector<value_type> &F) {
    const size_t size = F.size();
    const size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      const size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) std::swap(F[i], F[j]);
    }
    value_type coeff(1);
    for (size_t s = 0; s < logn; ++s) {
      const size_t mh = 1 << s;
      const size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = value_type(1);
        for (size_t j = i; j < i + mh; ++j) {
          const auto a = F[j];
          const auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= roots[s];
        }
      }
    }
  }

  static void inv_transform(std::vector<value_type> &F) {
    const size_t size = F.size();
    const size_t logn = bit_ctzr(size);
    for (size_t i = 0; i < size; ++i) {
      const size_t j = bit_rev(i) >> (64 - logn);
      if (i < j) std::swap(F[i], F[j]);
    }
    value_type coeff(1);
    for (size_t s = 0; s < logn; ++s) {
      const size_t mh = 1 << s;
      const size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = value_type(1);
        for (size_t j = i; j < i + mh; ++j) {
          const auto a = F[j];
          const auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= inv_roots[s];
        }
      }
    }
    coeff = inverse(value_type(size));
    for (auto &x: F) x *= coeff;
  }

};

/**
 * @title Number Theoretic Transform
 */