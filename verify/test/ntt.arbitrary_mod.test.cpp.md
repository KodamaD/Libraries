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


# :x: test/ntt.arbitrary_mod.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/ntt.arbitrary_mod.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-04 17:01:08+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod_1000000007">https://judge.yosupo.jp/problem/convolution_mod_1000000007</a>


## Depends on

* :question: <a href="../../library/algebraic/modular.cpp.html">algebraic/modular.cpp</a>
* :question: <a href="../../library/algebraic/ntt.cpp.html">algebraic/ntt.cpp</a>
* :question: <a href="../../library/other/bit_operation.cpp.html">other/bit_operation.cpp</a>
* :question: <a href="../../library/other/fast_io.cpp.html">other/fast_io.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../algebraic/ntt.cpp"
#include "../other/fast_io.cpp"

#include <iostream>
#include <vector>

fast_io::scanner cin;
fast_io::printer cout;

using m32 = modular<1000000007>;

int main() {
  size_t N, M;
  std::cin >> N >> M;
  std::vector<m32> A(N), B(M);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  for (auto &x: B) {
    std::cin >> x.extract();
  }
  auto C = convolve_arbitrary_mod(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    std::cout << C[i];
    std::cout << (i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/ntt.arbitrary_mod.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#line 2 "algebraic/ntt.cpp"

#line 2 "algebraic/modular.cpp"

#include <cstdint>
#include <iostream>

template <uint32_t Modulus>
class modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;

  static constexpr value_type mod = Modulus;
  static constexpr value_type get_mod() noexcept { return mod; }
  static_assert(mod >= 2, "invalid mod :: smaller than 2");
  static_assert(mod < (value_type(1) << 31), "invalid mod :: over 2^31");

  template <class T>
  static constexpr value_type normalize(T value_) noexcept {
    if (value_ < 0) {
      value_ = -value_;
      value_ %= mod;
      if (value_ == 0) return 0;
      return mod - value_;
    }
    return value_ % mod;
  }

private:
  value_type value;

public:
  constexpr modular() noexcept : value(0) { }
  template <class T>
  explicit constexpr modular(T value_) noexcept : value(normalize(value_)) { }
  template <class T>
  explicit constexpr operator T() const noexcept { return static_cast<T>(value); }

  constexpr value_type get() const noexcept { return value; }
  constexpr modular operator - () const noexcept { return modular(mod - value); }
  constexpr modular operator ~ () const noexcept { return inverse(); }

  constexpr value_type &extract() noexcept { return value; }
  constexpr modular inverse() const noexcept { return power(mod - 2); }
  constexpr modular power(max_type exp) const noexcept {
    modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  constexpr modular operator + (const modular &rhs) const noexcept { return modular(*this) += rhs; }
  constexpr modular& operator += (const modular &rhs) noexcept { 
    if ((value += rhs.value) >= mod) value -= mod; 
    return *this; 
  }

  constexpr modular operator - (const modular &rhs) const noexcept { return modular(*this) -= rhs; }
  constexpr modular& operator -= (const modular &rhs) noexcept { 
    if ((value += mod - rhs.value) >= mod) value -= mod; 
    return *this; 
  }

  constexpr modular operator * (const modular &rhs) const noexcept { return modular(*this) *= rhs; }
  constexpr modular& operator *= (const modular &rhs) noexcept { 
    value = (max_type) value * rhs.value % mod;
    return *this;
  }

  constexpr modular operator / (const modular &rhs) const noexcept { return modular(*this) /= rhs; }
  constexpr modular& operator /= (const modular &rhs) noexcept { return (*this) *= rhs.inverse(); }

  constexpr bool zero() const noexcept { return value == 0; }
  constexpr bool operator == (const modular &rhs) const noexcept { return value == rhs.value; }
  constexpr bool operator != (const modular &rhs) const noexcept { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) {
    return stream << rhs.value;
  }

};
#line 2 "other/bit_operation.cpp"

#include <cstddef>
#line 5 "other/bit_operation.cpp"

constexpr size_t count_zero_right(const uint64_t x) {
  return x == 0 ? 64 : __builtin_ctzll(x);
}

constexpr size_t count_zero_left(const uint64_t x) {
  return x == 0 ? 64 : __builtin_clzll(x);
}

constexpr size_t bit_width(const uint64_t x) { 
  return 64 - count_zero_left(x);
}

constexpr uint64_t most_significant_bit(const uint64_t x) {
  return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1);
}

constexpr uint64_t least_significant_bit(const uint64_t x) {
  return x & (-x);
}

constexpr uint64_t next_power_of_two(const uint64_t x) {
  return x == 0 ? 0 : most_significant_bit(2 * x - 1);
}

constexpr uint32_t bit_reverse_32(uint32_t x) {
  constexpr uint32_t b16 = 0b00000000000000001111111111111111;
  constexpr uint32_t  b8 = 0b00000000111111110000000011111111;
  constexpr uint32_t  b4 = 0b00001111000011110000111100001111;
  constexpr uint32_t  b2 = 0b00110011001100110011001100110011;
  constexpr uint32_t  b1 = 0b01010101010101010101010101010101;
  x = ((x >> 16) & b16) | ((x & b16) << 16);
  x = ((x >>  8) &  b8) | ((x &  b8) <<  8);
  x = ((x >>  4) &  b4) | ((x &  b4) <<  4);
  x = ((x >>  2) &  b2) | ((x &  b2) <<  2);
  x = ((x >>  1) &  b1) | ((x &  b1) <<  1);
  return x;
}
#line 6 "algebraic/ntt.cpp"
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

namespace ntt_detail {

  constexpr uint32_t calc_primitive_root(uint32_t mod) {
    std::array<uint32_t, 32> exp{};
    uint32_t cur = mod - 1;
    size_t size = 0;
    for (uint32_t i = 2; i * i <= cur; ++i) {
      if (cur % i == 0) {
        exp[size++] = (mod - 1) / i;
        while (cur % i == 0) cur /= i;
      }
    }
    if (cur != 1) {
      exp[size++] = (mod - 1) / cur;
    }
    uint32_t res = 2;
    while (true) {
      bool ok = true;
      for (size_t i = 0; i < size; ++i) {
        uint64_t a = res, e = exp[i], x = 1;
        while (e > 0) {
          if (e & 1) (x *= a) %= mod;
          (a *= a) %= mod;
          e >>= 1;
        }
        if (x == 1) {
          ok = false;
          break;
        }
      }
      if (ok) break;
      ++res;
    }
    return res;
  };

  template <size_t N, class T>
  constexpr std::array<T, N> calculate_roots(T omega) {
    std::array<T, N> res;
    res[N - 1] = omega;
    for (size_t i = N - 1; i > 0; --i) {
      res[i - 1] = res[i] * res[i];
    }
    return res;
  }

  template <class OtherModular, class Modular>
  constexpr OtherModular convert_mod(Modular x) {
    return OtherModular(x.get());
  }

  template <class OtherModular, class Modular>
  std::vector<OtherModular> convert_mod_vec(const std::vector<Modular> &vec) {
    std::vector<OtherModular> res(vec.size());
    std::transform(vec.cbegin(), vec.cend(), res.begin(), convert_mod<OtherModular, Modular>);
    return res;
  }

  namespace garner_mod {
    constexpr uint32_t m0 = 754974721;
    constexpr uint32_t m1 = 167772161;
    constexpr uint32_t m2 = 469762049;
    constexpr uint64_t m0m1 = (uint64_t) m0 * m1;
    constexpr auto im0_m1 = modular<m1>(m0).inverse();
    constexpr auto im0m1_m2 = modular<m2>(m0m1).inverse();
  };

  /*
    prime numbers for ntt
    [ 1051721729 ]  [ 2^20 ]
    [ 1045430273 ]  [ 2^20 ]
    [ 1007681537 ]  [ 2^20 ]
    [  962592769 ]  [ 2^21 ]
    [  924844033 ]  [ 2^21 ]
    [  985661441 ]  [ 2^22 ]
    [  943718401 ]  [ 2^22 ]
    [  935329793 ]  [ 2^22 ]
    [  998244353 ]  [ 2^23 ]
    [  754974721 ]  [ 2^24 ]
    [  167772161 ]  [ 2^25 ]
    [  469762049 ]  [ 2^26 ]
  */

}

template <class Modular>
class number_theoretic_transform {
public:
  using value_type = Modular;
  static constexpr uint32_t mod = Modular::get_mod();
  static constexpr uint32_t prim = ntt_detail::calc_primitive_root(mod);

private:
  static constexpr size_t level = count_zero_right(mod - 1);
  static constexpr value_type unit = value_type(1);
  static constexpr value_type omega = value_type(prim).power((mod - 1) >> level); 
  static constexpr auto roots = ntt_detail::calculate_roots<level>(omega);
  static constexpr auto inv_roots = ntt_detail::calculate_roots<level>(omega.inverse());

public:
  static void transform(std::vector<value_type> &F) {
    size_t size = F.size();
    size_t logn = count_zero_right(size);
    for (size_t i = 0; i < size; ++i) {
      size_t j = bit_reverse_32(i) >> (32 - logn);
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    value_type coeff = unit;
    for (size_t s = 0; s < logn; ++s) {
      size_t mh = 1 << s;
      size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = unit;
        for (size_t j = i; j < i + mh; ++j) {
          auto a = F[j];
          auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= roots[s];
        }
      }
    }
  }

  static void inv_transform(std::vector<value_type> &F) {
    size_t size = F.size();
    size_t logn = count_zero_right(size);
    for (size_t i = 0; i < size; ++i) {
      size_t j = bit_reverse_32(i) >> (32 - logn);
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    value_type coeff = unit;
    for (size_t s = 0; s < logn; ++s) {
      size_t mh = 1 << s;
      size_t m = mh << 1;
      for (size_t i = 0; i < size; i += m) {
        coeff = unit;
        for (size_t j = i; j < i + mh; ++j) {
          auto a = F[j];
          auto b = F[j + mh] * coeff;
          F[j] = a + b;
          F[j + mh] = a - b;
          coeff *= inv_roots[s];
        }
      }
    }
    coeff = value_type(size).inverse();
    for (auto &x: F) {
      x *= coeff;
    }
  }

  template <bool Same = false, typename std::enable_if<!Same, void>::type* = nullptr>
  static std::vector<value_type> convolve(
    std::vector<value_type> A, 
    std::vector<value_type> B) {
    if (A.empty() || B.empty()) return { };
    size_t res_size = A.size() + B.size() - 1;
    size_t fix_size = next_power_of_two(res_size);
    A.resize(fix_size);
    B.resize(fix_size);
    transform(A);
    transform(B);
    for (size_t i = 0; i < fix_size; ++i) {
      A[i] *= B[i];
    }
    inv_transform(A);
    A.resize(res_size);
    return A;
  }

  template <bool Same = false, typename std::enable_if<Same, void>::type* = nullptr>
  static std::vector<value_type> convolve(
    std::vector<value_type> A,
    [[maybe_unused]] const std::vector<value_type> &B) {
    if (A.empty()) return { };
    size_t res_size = 2 * A.size() - 1;
    size_t fix_size = next_power_of_two(res_size);
    A.resize(fix_size);
    transform(A);
    for (size_t i = 0; i < fix_size; ++i) {
      A[i] *= A[i];
    }
    inv_transform(A);
    A.resize(res_size);
    return A;
  }

  template <class OtherModular, bool Same = false>
  static std::vector<value_type> convolve_convert(
    const std::vector<OtherModular> &A, 
    const std::vector<OtherModular> &B) {
    return convolve<Same>(
      ntt_detail::convert_mod_vec<value_type>(A), 
      ntt_detail::convert_mod_vec<value_type>(B)
    );
  }

};

template <class Modular, bool Same = false>
std::vector<Modular> convolve_arbitrary_mod(
  const std::vector<Modular> &A, 
  const std::vector<Modular> &B) {
  using namespace ntt_detail::garner_mod;
  using ntt0 = number_theoretic_transform<modular<m0>>;
  using ntt1 = number_theoretic_transform<modular<m1>>;
  using ntt2 = number_theoretic_transform<modular<m2>>;
  auto X = ntt0::convolve_convert<Modular, Same>(A, B);
  auto Y = ntt1::convolve_convert<Modular, Same>(A, B);
  auto Z = ntt2::convolve_convert<Modular, Same>(A, B);
  size_t size = X.size();
  std::vector<Modular> res(size);
  for (size_t i = 0; i < size; ++i) {
    uint32_t s = (uint32_t) X[i];
    uint64_t t = (uint64_t) ((Y[i] - modular<m1>(s)) * im0_m1) * m0 + s;
    res[i] = Modular((__uint128_t) ((Z[i] - modular<m2>(t)) * im0m1_m2) * m0m1 + t);
  }
  return res;
}
#line 2 "other/fast_io.cpp"

#line 5 "other/fast_io.cpp"
#include <cstring>
#line 7 "other/fast_io.cpp"

namespace fast_io {
  static constexpr size_t buf_size = 1 << 18;
  static constexpr size_t buf_margin = 1;
  static constexpr size_t block_size = 10000;
  static constexpr size_t integer_size = 20;

  static char inbuf[buf_size + buf_margin] = {};
  static char outbuf[buf_size + buf_margin] = {};
  static char block_str[block_size * 4 + buf_margin] = {};

  static constexpr uint64_t power10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
    1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000,
    100000000000000, 1000000000000000, 10000000000000000, 100000000000000000,
    1000000000000000000, 10000000000000000000u
  };

  class scanner {
  private:
    size_t M_in_pos = 0, M_in_end = buf_size;

    void M_load() { 
      M_in_end = fread(inbuf, 1, buf_size, stdin); 
      inbuf[M_in_end] = '\0';  
    }
    void M_reload() {
      size_t length = M_in_end - M_in_pos;
      memmove(inbuf, inbuf + M_in_pos, length);
      M_in_end = length + fread(inbuf + length, 1, buf_size - length, stdin);
      inbuf[M_in_end] = '\0';
      M_in_pos = 0;
    }

    void M_ignore_space() {
      while (inbuf[M_in_pos] <= ' ') {
        if (__builtin_expect(++M_in_pos == M_in_end, 0)) M_reload();
      }
    }

    char M_next() { return inbuf[M_in_pos++]; }
    char M_next_nonspace() {
      M_ignore_space();
      return inbuf[M_in_pos++];
    }

  public:
    scanner() { M_load(); }
    
    void scan(char &c) { c = M_next_nonspace(); }
    void scan(std::string &s) {
      M_ignore_space();
      s = "";
      do {
        size_t start = M_in_pos;
        while (inbuf[M_in_pos] > ' ') ++M_in_pos;
        s += std::string(inbuf + start, inbuf + M_in_pos);
        if (inbuf[M_in_pos] != '\0') break;
        M_reload();
      } while (true);
    }

    template <class T>
    typename std::enable_if<std::is_integral<T>::value, void>::type scan(T &x) {
      char c = M_next_nonspace();
      if (__builtin_expect(M_in_pos + integer_size >= M_in_end, 0)) M_reload();
      bool n = false;
      if (c == '-') n = true, x = 0;
      else x = c & 15;
      while ((c = M_next()) >= '0') x = x * 10 + (c & 15);
      if (n) x = -x;
    }

    template <class T, class... Args>
    void scan(T &x, Args&... args) {
      scan(x); scan(args...);
    }

    template <class T>
    scanner& operator >> (T &x) {
      scan(x); return *this;
    }

  };

  class printer {
  private:
    size_t M_out_pos = 0;

    void M_flush() {
      fwrite(outbuf, 1, M_out_pos, stdout);
      M_out_pos = 0;
    }

    void M_precompute() {
      for (size_t i = 0; i < block_size; ++i) {
        size_t j = 4, k = i;
        while (j--) {
          block_str[i * 4 + j] = k % 10 + '0';
          k /= 10;
        }
      }
    }

    static constexpr size_t S_integer_digits(uint64_t n) {
      if (n >= power10[10]) {
        if (n >= power10[19]) return 20;
        if (n >= power10[18]) return 19;
        if (n >= power10[17]) return 18;
        if (n >= power10[16]) return 17;
        if (n >= power10[15]) return 16;
        if (n >= power10[14]) return 15;
        if (n >= power10[13]) return 14;
        if (n >= power10[12]) return 13;
        if (n >= power10[11]) return 12;
        return 11;
      }
      else {
        if (n >= power10[9]) return 10;
        if (n >= power10[8]) return 9;
        if (n >= power10[7]) return 8;
        if (n >= power10[6]) return 7;
        if (n >= power10[5]) return 6;
        if (n >= power10[4]) return 5;
        if (n >= power10[3]) return 4;
        if (n >= power10[2]) return 3;
        if (n >= power10[1]) return 2;
        return 1;
      }
    }

  public:
    printer() { M_precompute(); }
    ~printer() { M_flush(); }

    void print(char c) { 
      outbuf[M_out_pos++] = c;
      if (__builtin_expect(M_out_pos == buf_size, 0)) M_flush();
    }
    void print(const char *s) {
      while (*s != 0) {
        outbuf[M_out_pos++] = *s++;
        if (M_out_pos == buf_size) M_flush();
      }
    }
    void print(const std::string &s) {
      for (auto c: s) {
        outbuf[M_out_pos++] = c;
        if (M_out_pos == buf_size) M_flush();
      }
    }
    
    template <class T>
    typename std::enable_if<std::is_integral<T>::value, void>::type print(T x) {
      if (__builtin_expect(M_out_pos + integer_size >= buf_size, 0)) M_flush();
      if (x < 0) print('-'), x = -x;
      size_t digit = S_integer_digits(x);
      size_t len = digit;
      while (len >= 4) {
        len -= 4;
        memcpy(outbuf + M_out_pos + len, block_str + (x % block_size) * 4, 4);
        x /= 10000;
      }
      memcpy(outbuf + M_out_pos, block_str + x * 4 + 4 - len, len);
      M_out_pos += digit;
    }

    template <class T, class... Args>
    void print(const T &x, const Args&... args) {
      print(x); print(' '); print(args...);
    }

    template <class... Args>
    void println(const Args&... args) {
      print(args...); print('\n');
    }

    template <class T>
    printer& operator << (const T &x) {
      print(x); return *this;
    }

  };

};
#line 6 "test/ntt.arbitrary_mod.test.cpp"

#line 9 "test/ntt.arbitrary_mod.test.cpp"

fast_io::scanner cin;
fast_io::printer cout;

using m32 = modular<1000000007>;

int main() {
  size_t N, M;
  std::cin >> N >> M;
  std::vector<m32> A(N), B(M);
  for (auto &x: A) {
    std::cin >> x.extract();
  }
  for (auto &x: B) {
    std::cin >> x.extract();
  }
  auto C = convolve_arbitrary_mod(A, B);
  for (size_t i = 0; i < C.size(); ++i) {
    std::cout << C[i];
    std::cout << (i + 1 == C.size() ? '\n' : ' ');
  }
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

