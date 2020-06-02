
namespace detail {

  using u32 = uint_fast32_t;
  using u64 = uint_fast64_t;
  using u128 = __uint128_t;

  class modular64 {
  public:
    static inline u64 mod;
    static inline u64 encode;
    static inline u64 decode;

    static void set_mod(u64 x) {
      mod = x;
      encode = -u128(mod) % mod;
      decode = [] {
        u64 res = 0, cur = 0;
        for (size_t i = 0; i < 64; ++i) {
          if (!(cur & 1)) { res += u64(1) << i; cur += mod; }
          cur >>= 1;
        }
        return res;
      }();
    }
    static u64 reduce(u128 x) {
      u64 res = u64((u128(u64(x) * decode) * mod + x) >> 64);
      return res >= mod ? res - mod : res;
    }

  private:
    u64 value;

  public:
    explicit modular64(): value(0) { }
    explicit modular64(u64 x): value(reduce((u128) x * encode)) { }

    u64 get() const {
      u64 res = reduce(value);
      return res >= mod ? res - mod : res;
    }

    modular64 power(u64 exp) const {
      modular64 res(1), mult(*this);
      while (exp > 0) {
        if (exp & 1) res *= mult;
        mult *= mult;
        exp >>= 1;
      }
      return res;
    }

    modular64 operator + (const modular64 &rhs) const { return modular64(*this) += rhs; }
    modular64& operator += (const modular64 &rhs) { 
      if ((value += rhs.value) >= mod) value -= mod;
      return *this; 
    }
    modular64 operator * (const modular64 &rhs) const { return modular64(*this) *= rhs; }
    modular64& operator *= (const modular64 &rhs) { 
      value = reduce((u128) value * rhs.value);
      return *this;
    }
    bool operator == (const modular64 &rhs) const { return value == rhs.value; }
    bool operator != (const modular64 &rhs) const { return value != rhs.value; }

  };

  bool test_prime(u64 a, u64 s, u64 d, u64 n) {
    modular64::set_mod(n);
    modular64 cur = modular64(a).power(d);
    if (cur == modular64(1)) return true;
    modular64 bad(n - 1);
    for (size_t i = 0; i < s; ++i) {
      if (cur == bad) return true;
      cur *= cur;
    }
    return false;
  }

  template <class T>
  bool miller_rabin(T n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;
    uint_fast64_t d = n - 1, s = 0;
    while (!(d & 1)) { d >>= 1; ++s; }
    if (n < 4759123141) {
      for (auto p: { 2, 7, 61 }) {
        if (p != n && !test_prime(p, s, d, n)) return false;
      }
    } 
    else {
      for (auto p: { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
        if (p != n && !test_prime(p, s, d, n)) return false;
      }
    }
    return true;
  }

  template <class T>
  T pollard_rho(T n) {
    if (!(n & 1)) return 2;
    modular64::set_mod(n);
    modular64 add(1);
    auto transit = [&add](modular64 m) { return m * m + add; };
    auto dif_abs = [](u64 x, u64 y) { return x > y ? x - y : y - x; };
    u64 initial = 0;
    while (true) {
      ++initial;
      modular64 x(initial);
      modular64 y = transit(x);
      while (true) {
        u64 g = std::gcd(dif_abs(x.get(), y.get()), n);
        if (g == 1) {
          x = transit(x);
          y = transit(transit(y));
          continue;
        }
        if (g == n) break;
        return g;
      }
    }
  }

};

template <class T>
std::vector<T> enumerate_factors(T n) {
  if (n == 1) return { };
  if (detail::miller_rabin(n)) return { n };
  T d = detail::pollard_rho(n);
  std::vector<T> res = enumerate_factors(d);
  for (auto x: enumerate_factors(n / d)) {
    res.push_back(x);
  }
  return res;
}

template <class T>
std::vector<std::pair<T, size_t>> factorize(T n) {
  std::vector<std::pair<T, size_t>> res;
  auto factors = enumerate_factors(n);
  std::sort(factors.begin(), factors.end());
  T cur = 0;
  for (auto p: factors) {
    if (p != cur) {
      cur = p;
      res.emplace_back(p, 0);
    }
    ++res.back().second;
  }
  return res;
}

template <class T>
bool is_prime(T x) {
  return detail::miller_rabin(x);
}

template <class T>
std::vector<T> enumerate_divisors(T n, bool sort = true) {
  auto factors = factorize(n);
  std::vector<T> res;
  size_t size = 1;
  for (auto [p, e]: factors) {
    size *= (e + 1);
  }
  res.reserve(size);
  auto dfs = [&](auto dfs, size_t i, T x) -> void {
    if (i == factors.size()) {
      res.push_back(x);
      return;
    }
    dfs(dfs, i + 1, x);
    auto [p, e] = factors[i];
    for (size_t j = 1; j <= e; ++j) {
      x *= p;
      dfs(dfs, i + 1, x);
    }
  };
  dfs(dfs, 0, 1);
  if (sort) std::sort(res.begin(), res.end());
  return res;
}
