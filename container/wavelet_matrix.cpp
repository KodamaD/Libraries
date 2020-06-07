
template <class T, size_t W>
class wavelet_matrix {
public:
  using value_type = T;
  using size_type = size_t;

  static constexpr size_type word_size = W;

private:
  size_type size;
  std::array<bit_vector, word_size> fid;
  std::array<size_type, word_size> zero;

public:
  wavelet_matrix() = default;
  wavelet_matrix(const std::vector<value_type> &data_) { build(data_); }

  void build(std::vector<value_type> data_) {
    size = data_.size();
    std::vector<bool> bit(size);
    std::vector<value_type> next(size);
    for (size_type k = word_size; k--;) {
      auto l = next.begin(), r = next.rbegin();
      for (size_type i = 0; i < size; ++i) {
        bit[i] = data_[i] >> k & 1;
        (bit[i] ? *(r++) : *(l++)) = data_[i];
      }
      fid[k].build(bit);
      zero[k] = l - next.begin();
      std::reverse(next.rbegin(), r);
      data_.swap(next);
    }
  }

  size_type rank(value_type value, size_type l, size_type r) const {
    for (size_type k = word_size; k--;) {
      bool p = value >> k & 1;
      l = fid[k].rank(p, l) + p * zero[k];
      r = fid[k].rank(p, r) + p * zero[k];
    }
    return r - l;
  }

  size_type select(value_type value, size_type idx) const {
    std::array<size_type, word_size + 1> l, r;
    l[word_size] = 0;
    r[word_size] = size;
    for (size_type k = word_size; k--;) {
      bool p = value >> k & 1;
      l[k] = fid[k].rank(p, l[k + 1]) + p * zero[k];
      r[k] = fid[k].rank(p, r[k + 1]) + p * zero[k];
    }
    if (r[0] - l[0] <= idx) {
      return size;
    }
    for (size_type k = 0; k < word_size; ++k) {
      bool p = value >> k & 1;
      idx = fid[k].select(p, idx, l[k + 1]) - l[k + 1];
    }
    return idx;
  }

  value_type access(size_type idx) const {
    value_type res = 0;
    for (size_type k = word_size; k--;) {
      bool p = fid[k].access(idx);
      res |= value_type(p) << k;
      idx = fid[k].rank(p, idx) + p * zero[k];
    }
    return res;
  }

  value_type quantile(size_type idx, size_type l, size_type r) const {
    value_type res = 0;
    for (size_type k = word_size; k--;) {
      size_type lc = fid[k].rank(1, l);
      size_type rc = fid[k].rank(1, r);
      size_type zc = (r - l) - (rc - lc);
      bool p = (idx >= zc);
      res |= value_type(p) << k;
      if (p) {
        l = lc + zero[k];
        r = rc + zero[k];
        idx -= zc;
      }
      else {
        l -= lc;
        r -= rc;
      }
    }
    return res;
  }

  size_type count(size_type l, size_type r, value_type value) const {
    size_type res = 0;
    for (size_type k = word_size; k--;) {
      size_type lc = fid[k].rank(1, l);
      size_type rc = fid[k].rank(1, r);
      if (value >> (k) & 1) {
        l = lc + zero[k];
        r = rc + zero[k];
      }
      else {
        l -= lc;
        r -= rc;
        res += (rc - lc);
      }
    }
    return res + (r - l);
  }
  size_type count(size_type l, size_type r, value_type lb, value_type ub) const {
    return count(l, r, lb) - count(l, r, ub);
  }

};
