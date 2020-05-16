
template <class T>
class fast_fourier_transform {
public:
  using value_type = T;
  using size_type = size_t;
  static constexpr value_type pi = std::acos(value_type(-1.0));

  struct complex {
    value_type re, im;
    constexpr complex(value_type re_ = 0, value_type im_ = 0): re(re_), im(im_) { }
    constexpr complex operator + (const complex &rhs) const { 
      return complex(re + rhs.re, im + rhs.im); 
    }
    constexpr complex operator - (const complex &rhs) const { 
      return complex(re - rhs.re, im - rhs.im); 
    }
    constexpr complex operator * (const complex &rhs) const { 
      return complex(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re); 
    }
  };

private:
  size_type M_size;
  std::vector<complex> M_root;

public:
  template <class U>
  std::vector<U> convolve(const std::vector<U> &A, const std::vector<U> &B) {
    size_type res_size = A.size() + B.size() - 1;
    reserve(res_size);
    std::vector<complex> C(M_size), D(M_size);
    for (size_type i = 0; i < A.size(); ++i) {
      C[i].re = static_cast<value_type>(A[i]);
    }
    for (size_type i = 0; i < B.size(); ++i) {
      D[i].re = static_cast<value_type>(B[i]);
    }
    discrete_fourier_transform(C);
    discrete_fourier_transform(D);
    for (size_type i = 0; i < M_size; ++i) {
      C[i] = C[i] * D[i];
    }
    inverse_discrete_fourier_transform(C);
    std::vector<U> res(res_size);
    for (size_type i = 0; i < res_size; ++i) {
      res[i] = static_cast<U>(C[i].re / M_size + value_type(0.5));
    }
    return res;
  }

  void reserve(size_type size_) {
    M_size = 1;
    while (M_size < size_) M_size <<= 1;
    M_root.assign(M_size + 1, complex());
    for (size_type i = 0; i <= M_size; ++i) {
      value_type angle = pi * value_type(2.0) / M_size * i;
      M_root[i].re = std::cos(angle);
      M_root[i].im = std::sin(angle);
    }
  }

  void discrete_fourier_transform(std::vector<complex> &F) {
    for (size_type i = 0, j = 1; j + 1 < M_size; ++j) {
      size_type k = M_size >> 1;
      while (k > (i ^= k)) k >>= 1;
      if (i < j) std::swap(F[i], F[j]);
    }
    size_type idx;
    complex first, second;
    for (size_type len = 1, bit = M_size >> 1; len < M_size; len <<= 1, bit >>= 1) {
      for (size_type k = 0; k < M_size; k += (len << 1)) {
        idx = 0;
        for (size_type i = 0; i < len; ++i) {
          first = F[i + k], second = F[(i + k) ^ len];
          F[i + k] = M_root[0] * first + M_root[idx] * second;
          F[(i + k) ^ len] = M_root[0] * first + M_root[idx + (M_size >> 1)] * second;
          idx += bit;
        }
      }
    }
  }

  void inverse_discrete_fourier_transform(std::vector<complex> &F) {
    for (size_type i = 0, j = 1; j + 1 < M_size; ++j) {
      size_type k = M_size >> 1;
      while (k > (i ^= k)) k >>= 1;
      if (i < j) std::swap(F[i], F[j]);
    }
    size_type idx;
    complex first, second;
    for (size_type len = 1, bit = M_size >> 1; len < M_size; len <<= 1, bit >>= 1) {
      for (size_type k = 0; k < M_size; k += (len << 1)) {
        idx = M_size;
        for (size_type i = 0; i < len; ++i) {
          first = F[i + k], second = F[(i + k) ^ len];
          F[i + k] = M_root[0] * first + M_root[idx] * second;
          F[(i + k) ^ len] = M_root[0] * first + M_root[idx - (M_size >> 1)] * second;
          idx -= bit;
        }
      }
    }
  }

};
