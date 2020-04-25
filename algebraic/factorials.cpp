
template <class T, std::size_t N>
class factorials {
public:
  using value_type = T;
  static constexpr std::size_t size = N;

public:
  std::array<value_type, size + 1> fact{};
  std::array<value_type, size + 1> fact_inv{};

  constexpr factorials() {
    fact.front() = value_type(1);
    for (std::size_t i = 1; i <= size; ++i) {
      fact[i] = fact[i - 1] * value_type(i);
    }
    fact_inv.back() = ~fact.back();
    for (std::size_t i = size; i > 0; --i) {
      fact_inv[i - 1] = fact_inv[i] * value_type(i);
    }
  }

  constexpr value_type operator () (std::size_t n, std::size_t r) const {
    return fact[n] * fact_inv[n - r] * fact_inv[r];
  }

};
