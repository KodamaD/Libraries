
template <class T>
class fast_fourier_transform {
public:
  using value_type = T;
  static constexpr value_type pi = std::acos(value_type(-1.0));

  struct complex_type {
    value_type re, im;
    constexpr complex_type(value_type re_ = 0, value_type im_ = 0): re(re_), im(im_) { }
    constexpr complex_type operator + (const complex_type &rhs) const { 
      return complex_type(re + rhs.re, im + rhs.im); 
    }
    constexpr complex_type operator - (const complex_type &rhs) const { 
      return complex_type(re - rhs.re, im - rhs.im); 
    }
    constexpr complex_type operator * (const complex_type &rhs) const { 
      return complex_type(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re); 
    }
  };

private:
  size_t M_size;
  std::vector<complex_type> M_root;

public:
  void reserve(size_t size_) {
    M_size = 1;
    while (M_size < size_) M_size <<= 1;
    M_root.assign(M_size + 1, complex_type());
    for (size_t i = 0; i <= M_size; ++i) {
      value_type angle = pi * value_type(2.0) / M_size * i;
      M_root[i].re = std::cos(angle);
      M_root[i].im = std::sin(angle);
    }
  }

  void transform(std::vector<complex_type> &F) const {
    for (size_t i = 0, j = 1; j + 1 < M_size; ++j) {
      size_t k = M_size >> 1;
      while (k > (i ^= k)) k >>= 1;
      if (i < j) std::swap(F[i], F[j]);
    }
    size_t idx;
    complex_type first, second;
    for (size_t len = 1, bit = M_size >> 1; len < M_size; len <<= 1, bit >>= 1) {
      for (size_t k = 0; k < M_size; k += (len << 1)) {
        idx = 0;
        for (size_t i = 0; i < len; ++i) {
          first = F[i + k], second = F[(i + k) ^ len];
          F[i + k] = M_root[0] * first + M_root[idx] * second;
          F[(i + k) ^ len] = M_root[0] * first + M_root[idx + (M_size >> 1)] * second;
          idx += bit;
        }
      }
    }
  }

  void inv_transform(std::vector<complex_type> &F) const {
    for (size_t i = 0, j = 1; j + 1 < M_size; ++j) {
      size_t k = M_size >> 1;
      while (k > (i ^= k)) k >>= 1;
      if (i < j) std::swap(F[i], F[j]);
    }
    size_t idx;
    complex_type first, second;
    for (size_t len = 1, bit = M_size >> 1; len < M_size; len <<= 1, bit >>= 1) {
      for (size_t k = 0; k < M_size; k += (len << 1)) {
        idx = M_size;
        for (size_t i = 0; i < len; ++i) {
          first = F[i + k], second = F[(i + k) ^ len];
          F[i + k] = M_root[0] * first + M_root[idx] * second;
          F[(i + k) ^ len] = M_root[0] * first + M_root[idx - (M_size >> 1)] * second;
          idx -= bit;
        }
      }
    }
  }

  template <class U>
  std::vector<U> convolve(const std::vector<U> &A, const std::vector<U> &B) {
    size_t res_size = A.size() + B.size() - 1;
    reserve(res_size);
    std::vector<complex_type> C(M_size), D(M_size);
    for (size_t i = 0; i < A.size(); ++i) {
      C[i].re = static_cast<value_type>(A[i]);
    }
    for (size_t i = 0; i < B.size(); ++i) {
      D[i].re = static_cast<value_type>(B[i]);
    }
    transform(C);
    transform(D);
    for (size_t i = 0; i < M_size; ++i) {
      C[i] = C[i] * D[i];
    }
    inv_transform(C);
    std::vector<U> res(res_size);
    for (size_t i = 0; i < res_size; ++i) {
      res[i] = static_cast<U>(C[i].re / M_size + value_type(0.5));
    }
    return res;
  }

};
