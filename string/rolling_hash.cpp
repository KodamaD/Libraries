
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

namespace rlh {

  using ulint = unsigned long long;
  constexpr ulint RH_MOD = (1ull << 61) - 1;
  constexpr ulint MASK30 = (1ull << 30) - 1;
  constexpr ulint MASK31 = (1ull << 31) - 1;

  constexpr ulint normalize(const ulint& x) {
    ulint res = (x & RH_MOD) + (x >> 61);
    if(res > RH_MOD)res -= RH_MOD;
    return res;
  }

  constexpr ulint multiply(const ulint& a, const ulint& b) {
    ulint au = a >> 31, ad = a & MASK31;
    ulint bu = b >> 31, bd = b & MASK31;
    ulint mid = ad * bu + au * bd, midu = mid >> 30, midd = mid & MASK30;
    return normalize(au * bu * 2 + midu + (midd << 31) + ad * bd);
  }

  struct rolling_hash_base {
    unsigned int base1, base2;
    rolling_hash_base() {
      std::srand((unsigned)std::clock() + (unsigned)std::time(nullptr));
      base1 = std::rand() % 1024 + 256;
      base2 = std::rand() % 1024 + 256;
    }
  } rh_base;

  class rolling_hash {
  private:
    int str_sz;
    std::string str;
    std::vector<ulint> hash1, hash2, pow1, pow2;

  public:
    rolling_hash() { }
    rolling_hash(const std::string& str_) { init(str_); }

    void init(const std::string& str_) {
      str_sz = str_.size();
      str = str_;
      hash1.assign(str_sz + 1, 0); 
      hash2.assign(str_sz + 1, 0);
      pow1.assign(str_sz + 1, 1); 
      pow2.assign(str_sz + 1, 1);
      for (int i = 0; i < str_sz; ++i) {
        hash1[i + 1] = normalize(multiply(hash1[i], rh_base.base1) + str_[i]);
        hash2[i + 1] = normalize(multiply(hash2[i], rh_base.base2) + str_[i]);
        pow1[i + 1] = multiply(pow1[i], rh_base.base1);
        pow2[i + 1] = multiply(pow2[i], rh_base.base2);
      }
    }

    void add_string(const std::string& str_) {
      int tmp_sz = str_sz;
      str_sz += str_.size();
      str += str_;
      hash1.resize(str_sz + 1); 
      hash2.resize(str_sz + 1);
      pow1.resize(str_sz + 1); 
      pow2.resize(str_sz + 1);
      for (int i = tmp_sz; i < str_sz; ++i) {
        hash1[i + 1] = normalize(multiply(hash1[i], rh_base.base1) + str_[i - tmp_sz]);
        hash2[i + 1] = normalize(multiply(hash2[i], rh_base.base2) + str_[i - tmp_sz]);
        pow1[i + 1] = multiply(pow1[i], rh_base.base1);
        pow2[i + 1] = multiply(pow2[i], rh_base.base2);
      }
    }

    void add_char(const char& c) {
      str += c;
      ++str_sz;
      hash1.emplace_back(normalize(multiply(hash1.back(), rh_base.base1) + c));
      hash2.emplace_back(normalize(multiply(hash2.back(), rh_base.base2) + c));
      pow1.emplace_back(multiply(pow1.back(), rh_base.base1));
      pow2.emplace_back(multiply(pow2.back(), rh_base.base2));
    }

    const std::string& operator () () const {
      return str;
    }

    std::pair<ulint, ulint> hash(const int& l, const int& r) const {
      ulint res1 = normalize(hash1[r] + RH_MOD - multiply(hash1[l], pow1[r - l]));
      ulint res2 = normalize(hash2[r] + RH_MOD - multiply(hash2[l], pow2[r - l]));
      return std::make_pair(res1, res2);
    }

    int lcp(const int& l, const int& r) const {
      int ok = 0, ng = std::min(str_sz - l, str_sz - r) + 1;
      while (ng - ok > 1) {
        int md = (ok + ng) >> 1;
        (hash(l, l + md) == hash(r, r + md) ? ok : ng) = md;
      }
      return ok;
    }

  };

};

int main() {
  return 0;
}