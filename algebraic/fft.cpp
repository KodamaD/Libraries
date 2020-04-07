
namespace fft {
  using real_type = double;
  constexpr real_type pi = std::acos(-1.0L);

  struct complex {
    real_type re, im;
    complex(real_type re_ = 0, real_type im_ = 0): re(re_), im(im_) { }
    inline complex operator + (const complex &rhs) const { 
      return complex(re + rhs.re, im + rhs.im); 
    }
    inline complex operator - (const complex &rhs) const { 
      return complex(re - rhs.re, im - rhs.im); 
    }
    inline complex operator * (const complex &rhs) const { 
      return complex(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re); 
    }
  };

  int size;
  std::vector<complex> root;
  void reserve(int size_) {
    size = 1;
    while (size < size_) {
      size <<= 1;
    }
    root.assign(size + 1, complex());
    for (int i = 0; i <= size; ++i) {
      real_type angle = pi * 2.0L / size * i;
      root[i] = complex(cosl(angle), sinl(angle));
    }
  }

  void discrete_fourier_transform(std::vector<complex> &F) {
    for (int i = 0, j = 1; j + 1 < size; ++j) {
      int k = size >> 1;
      while (k > (i ^= k)) {
        k >>= 1;
      }
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    int idx;
    complex first, second;
    for (int len = 1, bit = (size >> 1); len < size; len <<= 1, bit >>= 1) {
      for (int k = 0; k < size; k += (len << 1)) {
        idx = 0;
        for (int i = 0; i < len; ++i) {
          first = F[i + k];
          second = F[(i + k) ^ len];
          F[i + k] = root[0] * first + root[idx] * second;
          F[(i + k) ^ len] = root[0] * first + root[idx + (size >> 1)] * second;
          idx += bit;
        }
      }
    }
  }

  void inverse_discrete_fourier_transform(std::vector<complex> &F) {
    for (int i = 0, j = 1; j + 1 < size; ++j) {
      int k = size >> 1;
      while (k > (i ^= k)) {
        k >>= 1;
      }
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    int idx;
    complex first, second;
    for (int len = 1, bit = (size >> 1); len < size; len <<= 1, bit >>= 1) {
      for (int k = 0; k < size; k += (len << 1)) {
        idx = size;
        for (int i = 0; i < len; ++i) {
          first = F[i + k];
          second = F[(i + k) ^ len];
          F[i + k] = root[0] * first + root[idx] * second;
          F[(i + k) ^ len] = root[0] * first + root[idx - (size >> 1)] * second;
          idx -= bit;
        }
      }
    }
  }

  template <class T>
  std::vector<T> convolve(const std::vector<T> &A, const std::vector<T> &B) {
    int res_size = A.size() + B.size() - 1;
    reserve(res_size);
    std::vector<complex> C(size), D(size);
    for (int i = 0; i < A.size(); ++i) {
      C[i].re = static_cast<real_type>(A[i]);
    }
    for (int i = 0; i < B.size(); ++i) {
      D[i].re = static_cast<real_type>(B[i]);
    }
    discrete_fourier_transform(C);
    discrete_fourier_transform(D);
    for (int i = 0; i < size; ++i) {
      C[i] = C[i] * D[i];
    }
    inverse_discrete_fourier_transform(C);
    std::vector<T> res(res_size);
    for (int i = 0; i < res_size; ++i) {
      res[i] = static_cast<T>(C[i].re / size + 0.5L);
    }
    return res;
  }

};
