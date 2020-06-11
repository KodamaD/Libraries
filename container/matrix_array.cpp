
template <class T, size_t H, size_t W>
class matrix {
public:
  using value_type = typename T::value_type;
  using size_type = size_t;

  static inline auto add = typename T::addition();
  static inline auto mult = typename T::multiplication();

  static constexpr size_type height = H;
  static constexpr size_type width = W;

private:
  std::array<std::array<value_type, W>, H> M_data;

public:
  matrix(const value_type &value_ = add.identity) { fill(value_); }
  matrix(const std::array<std::array<value_type, W>, H> &data_): M_data(data_) { }

  std::array<value_type, W> &operator [] (size_type idx) { return M_data[idx]; }
  const std::array<value_type, W> &operator [] (size_type idx) const { return M_data[idx]; }

  matrix operator + (const matrix &rhs) const { return matrix(*this) += rhs; }
  matrix &operator += (const matrix &rhs) {
    for (size_type i = 0; i < H; ++i) {
      for (size_type j = 0; j < W; ++j) {
        M_data[i][j] = add(M_data[i][j], rhs[i][j]);
      }
    }
    return *this;
  }

  matrix &operator *= (const matrix<T, W, W> &rhs) { return (*this) = (*this) * rhs; }
  template <size_t K>
  matrix<T, H, K> operator * (const matrix<T, W, K> &rhs) const {
    matrix<T, H, K> res;
    for (size_type i = 0; i < H; ++i) {
      for (size_type j = 0; j < K; ++j) {
        for (size_type k = 0; k < W; ++k) {
          res[i][j] = add(res[i][j], mult(M_data[i][k], rhs[k][j]));
        }
      }
    }
    return res;
  }

  matrix operator * (const value_type &rhs) const { return matrix(*this) *= rhs; }
  matrix &operator *= (const value_type &rhs) {
    for (size_type i = 0; i < H; ++i) {
      for (size_type j = 0; j < W; ++j) {
        M_data[i][j] = mult(M_data[i][j], rhs);
      }
    }
    return *this;
  }

  void fill(const value_type &val) {
    for (auto &arr: M_data) { arr.fill(val); }
  }
  typename std::enable_if<H == W, matrix>::type power(uint64_t exp) const {
    matrix res, use(*this);
    for (size_type i = 0; i < H; ++i) {
      res[i][i] = mult.identity;
    }
    while (exp > 0) {
      if (exp & 1) res *= use;
      use *= use;
      exp >>= 1;
    }
    return res;
  }

};