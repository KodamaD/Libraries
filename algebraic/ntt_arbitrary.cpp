#pragma once

#include "../algebraic/ntt.cpp"
#include <vector>

namespace ntt_arbitrary_detail {

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

  template <class NTT, class OtherModular, bool Same = false>
  std::vector<typename NTT::value_type> convolve_convert(
    const std::vector<OtherModular> &A, 
    const std::vector<OtherModular> &B) {
    return NTT::template convolve<Same>(
      convert_mod_vec<typename NTT::value_type>(A),
      convert_mod_vec<typename NTT::value_type>(B)
    );
  }

  namespace garner_mod {
    constexpr uint32_t m0 = 754974721;
    constexpr uint32_t m1 = 167772161;
    constexpr uint32_t m2 = 469762049;
    constexpr uint64_t m0m1 = (uint64_t) m0 * m1;
    constexpr auto im0_m1 = modular<m1>(m0).inverse();
    constexpr auto im0m1_m2 = modular<m2>(m0m1).inverse();
  };

};

template <class Modular, bool Same = false>
std::vector<Modular> convolve_arbitrary_mod(
  const std::vector<Modular> &A, 
  const std::vector<Modular> &B) {
  using namespace ntt_arbitrary_detail;
  using namespace garner_mod;
  using ntt0 = number_theoretic_transform<modular<m0>>;
  using ntt1 = number_theoretic_transform<modular<m1>>;
  using ntt2 = number_theoretic_transform<modular<m2>>;
  auto X = convolve_convert<ntt0, Modular, Same>(A, B);
  auto Y = convolve_convert<ntt1, Modular, Same>(A, B);
  auto Z = convolve_convert<ntt2, Modular, Same>(A, B);
  size_t size = X.size();
  std::vector<Modular> res(size);
  for (size_t i = 0; i < size; ++i) {
    uint32_t s = (uint32_t) X[i];
    uint64_t t = (uint64_t) ((Y[i] - modular<m1>(s)) * im0_m1) * m0 + s;
    res[i] = Modular((__uint128_t) ((Z[i] - modular<m2>(t)) * im0m1_m2) * m0m1 + t);
  }
  return res;
}
