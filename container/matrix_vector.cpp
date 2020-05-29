
template <class T>
class matrix {
public:
  using value_type = typename T::value_type;
  using size_type = size_t;

  static inline const auto add = typename T::addition();
  static inline const auto mult = typename T::multiplication();

private:
  std::vector<std::vector<value_type>> data;

public:
  size_type height, width;

  matrix() = default;
  matrix(size_type height_, size_type width_, const value_type &value_ = add.identity):
    data(height_, std::vector<value_type>(width_, value_)),
    height(height_), width(width_)
  { }
  matrix(const std::vector<std::vector<value_type>> &data_):
    data(data_),
    height(data_.size()), width(data_.front().size())
  { }

  std::vector<value_type> &operator [] (size_type idx) { return data[idx]; }
  const std::vector<value_type> &operator [] (size_type idx) const { return data[idx]; }

  matrix operator + (const matrix &rhs) const { return matrix(*this) += rhs; }
  matrix& operator += (const matrix &rhs) { 
    for (size_type i = 0; i < height; ++i) {
      for (size_type j = 0; j < width; ++j) {
        data[i][j] = add(data[i][j], rhs[i][j]);
      }
    }
    return *this;
  }

  matrix& operator *= (const matrix &rhs) { *this = (*this) * rhs; return *this; }
  matrix operator * (const matrix &rhs) const {
    matrix res(height, rhs.width);
    for (size_type i = 0; i < height; ++i) {
      for (size_type j = 0; j < rhs.width; ++j) {
        for (size_type k = 0; k < width; ++k) {
          res[i][j] = add(res[i][j], mult(data[i][k], rhs[k][j]));
        }
      }
    }
    return res;
  }

  matrix operator * (const value_type &rhs) const { return matrix(*this) *= rhs; }
  matrix& operator *= (const value_type &rhs)  { 
    for (size_type i = 0; i < height; ++i) {
      for (size_type j = 0; j < width; ++j) {
        data[i][j] = mult(data[i][j], rhs);
      }
    }
    return *this;
  }

  matrix power(uint64_t exp) const {
    matrix res(height, width), use(*this);
    for (size_type i = 0; i < height; ++i) {
      res[i][i] = mult.identity;
    }
    while (exp > 0) {
      if (exp & 1) {
        res *= use;
      }
      use *= use;
      exp >>= 1;
    }
    return res;
  }

};
