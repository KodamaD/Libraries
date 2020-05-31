
template <uint32_t Modulus>
class modular {
public:
  using value_type = uint32_t;
  using max_type = uint64_t;

  static constexpr value_type mod = Modulus;
  static constexpr value_type mod_min = 1;
  static constexpr value_type mod_max = 2147483647;
  static_assert(mod >= mod_min, "invalid mod :: too small");
  static_assert(mod <= mod_max, "invalid mod :: too big");

  template <class T>
  static constexpr value_type normalize(T value_) {
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
  constexpr modular(): value(0) { }
  template <class T>
  explicit constexpr modular(T value_): value(normalize(value_)) { }
  template <class T>
  explicit constexpr operator T() { return static_cast<T>(value); }

  constexpr value_type operator () () const { return value; }
  constexpr modular operator - () const { return modular(mod - value); }
  constexpr modular operator ~ () const { return inverse(); }

  constexpr value_type &extract() { return value; }
  constexpr modular inverse() const { return power(mod - 2); }
  constexpr modular power(max_type exp) const {
    modular res(1), mult(*this);
    while (exp > 0) {
      if (exp & 1) res *= mult;
      mult *= mult;
      exp >>= 1;
    }
    return res;
  }

  constexpr modular operator + (const modular &rhs) const { return modular(*this) += rhs; }
  constexpr modular& operator += (const modular &rhs) { 
    if ((value += rhs.value) >= mod) value -= mod; 
    return *this; 
  }

  constexpr modular operator - (const modular &rhs) const { return modular(*this) -= rhs; }
  constexpr modular& operator -= (const modular &rhs) { 
    if ((value += mod - rhs.value) >= mod) value -= mod; 
    return *this; 
  }

  constexpr modular operator * (const modular &rhs) const { return modular(*this) *= rhs; }
  constexpr modular& operator *= (const modular &rhs) { 
    value = (max_type) value * rhs.value % mod;
    return *this;
  }

  constexpr modular operator / (const modular &rhs) const { return modular(*this) /= rhs; }
  constexpr modular& operator /= (const modular &rhs) { return (*this) *= rhs.inverse(); }

  constexpr bool zero() const { return value == 0; }
  constexpr bool operator == (const modular &rhs) const { return value == rhs.value; }
  constexpr bool operator != (const modular &rhs) const { return value != rhs.value; }
  friend std::ostream& operator << (std::ostream &stream, const modular &rhs) {
    return stream << rhs.value;
  }

};

using m32 = modular<1000000007>;
