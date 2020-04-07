
template <class T>
class factorials {
public:
  using value_type = T;

public:
  std::vector<value_type> fact, fact_inv;

  factorials(int size_ = 200000): fact(size_ + 1), fact_inv(size_ + 1) {
    fact[0] = 1;
    for (int i = 1; i <= size_; ++i) {
      fact[i] = fact[i - 1] * value_type(i);
    }
    fact_inv[size_] = ~fact[size_];
    for (int i = size_; i > 0; --i) {
      fact_inv[i - 1] = fact_inv[i] * value_type(i);
    }
  }

  value_type operator () (int n, int r) const {
    return fact[n] * fact_inv[n - r] * fact_inv[r];
  }

};
