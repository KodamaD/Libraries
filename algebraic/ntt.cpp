
namespace detail {

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

  namespace bit_operation {
    constexpr uint32_t b16 = 0b00000000000000001111111111111111;
    constexpr uint32_t  b8 = 0b00000000111111110000000011111111;
    constexpr uint32_t  b4 = 0b00001111000011110000111100001111;
    constexpr uint32_t  b2 = 0b00110011001100110011001100110011;
    constexpr uint32_t  b1 = 0b01010101010101010101010101010101;
    constexpr size_t reverse(size_t x) {
      x = ((x >> 16) & b16) | ((x & b16) << 16);
      x = ((x >>  8) &  b8) | ((x &  b8) <<  8);
      x = ((x >>  4) &  b4) | ((x &  b4) <<  4);
      x = ((x >>  2) &  b2) | ((x &  b2) <<  2);
      x = ((x >>  1) &  b1) | ((x &  b1) <<  1);
      return x;
    }
  };

  namespace garner_mod {
    constexpr uint32_t m0 = 998244353;
    constexpr uint32_t m1 = 935329793;
    constexpr uint32_t m2 = 943718401;
    constexpr uint32_t p0 = 3;
    constexpr uint32_t p1 = 3;
    constexpr uint32_t p2 = 7;
    constexpr uint64_t m0m1 = (uint64_t) m0 * m1;
    constexpr auto im0_m1 = modular<m1>(m0).inverse();
    constexpr auto im0m1_m2 = modular<m2>(m0m1).inverse();
  };

  /*
    prime numbers for ntt
    [ 1051721729, 6 ]  [ 2^20 ]
    [ 1045430273, 3 ]  [ 2^20 ]
    [ 1007681537, 3 ]  [ 2^20 ]
    [  962592769, 7 ]  [ 2^21 ]
    [  924844033, 5 ]  [ 2^21 ]
    [  985661441, 3 ]  [ 2^22 ]
    [  943718401, 7 ]  [ 2^22 ]
    [  935329793, 3 ]  [ 2^22 ]
    [  998244353, 3 ]  [ 2^23 ]
  */

}

template <uint32_t Modulus, uint32_t PrimRoot, class Modular = modular<Modulus>>
class number_theoretic_transform {
public:
  using value_type = Modular;
  static constexpr uint32_t mod = Modulus;
  static constexpr uint32_t prim = PrimRoot;

private:
  static constexpr size_t level = __builtin_ctz(mod - 1);
  static constexpr value_type unit = value_type(1);
  static constexpr value_type omega = value_type(prim).power((mod - 1) >> level); 
  static constexpr auto roots = detail::calculate_roots<level>(omega);
  static constexpr auto inv_roots = detail::calculate_roots<level>(omega.inverse());

  void M_transform(std::vector<value_type> &F) const {
    size_t size = F.size();
    size_t logn = __builtin_ctz(size);
    for (size_t i = 0; i < size; ++i) {
      size_t j = detail::bit_operation::reverse(i) >> (32 - logn);
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

  void M_inv_transform(std::vector<value_type> &F) const {
    size_t size = F.size();
    size_t logn = __builtin_ctz(size);
    for (size_t i = 0; i < size; ++i) {
      size_t j = detail::bit_operation::reverse(i) >> (32 - logn);
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

public:
  std::vector<value_type> convolve(std::vector<value_type> A, std::vector<value_type> B) const {
    if (A.empty() || B.empty()) return { };
    size_t res_size = A.size() + B.size() - 1;
    size_t fix_size = 1 << (31 - __builtin_clz(2 * res_size - 1));
    if (A == B) {
      A.resize(fix_size);
      M_transform(A);
      for (size_t i = 0; i < fix_size; ++i) {
        A[i] *= A[i];
      }
      M_inv_transform(A);
      A.resize(res_size);
      return A;
    }
    else {
      A.resize(fix_size);
      B.resize(fix_size);
      M_transform(A);
      M_transform(B);
      for (size_t i = 0; i < fix_size; ++i) {
        A[i] *= B[i];
      }
      M_inv_transform(A);
      A.resize(res_size);
      return A;
    }
  }

  template <class OtherModular>
  std::vector<value_type> convolve_convert(const std::vector<OtherModular> &A, const std::vector<OtherModular> &B) const {
    return convolve(detail::convert_mod_vec<value_type>(A), detail::convert_mod_vec<value_type>(B));
  }

};

template <class Modular>
std::vector<Modular> arbitrary_mod_convolution(const std::vector<Modular> &A, const std::vector<Modular> &B) {
  using namespace detail::garner_mod;
  number_theoretic_transform<m0, p0> ntt0;
  number_theoretic_transform<m1, p1> ntt1;
  number_theoretic_transform<m2, p2> ntt2;
  auto X = ntt0.convolve_convert(A, B);
  auto Y = ntt1.convolve_convert(A, B);
  auto Z = ntt2.convolve_convert(A, B);
  size_t size = X.size();
  std::vector<Modular> res(size);
  for (size_t i = 0; i < size; ++i) {
    uint32_t s = (uint32_t) X[i];
    uint64_t t = (uint64_t) ((Y[i] - modular<m1>(s)) * im0_m1) * m0 + s;
    res[i] = Modular((__uint128_t) ((Z[i] - modular<m2>(t)) * im0m1_m2) * m0m1 + t);
  }
  return res;
}
