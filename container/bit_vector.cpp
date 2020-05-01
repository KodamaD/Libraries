
class bit_vector {
public:
  using size_type = size_t;
  using bit_type = uint64_t;
  using count_type = uint32_t;

  static constexpr size_type block_size = 64;

private:
  size_type size;
  std::vector<bit_type> block;
  std::vector<count_type> accum;

public:
  bit_vector() = default;
  bit_vector(const std::vector<bool> &data_) { build(data_); }

  void build(const std::vector<bool> &data_) {
    size = data_.size();
    size_type fixed_size = size / block_size + 1;
    block.assign(fixed_size, 0);
    accum.assign(fixed_size, 0);
    for (size_type i = 0; i < size; ++i) {
      if (data_[i]) {
        block[i / block_size] |= (1ull << (i & (block_size - 1)));
      }
    }
    for (size_type i = 1; i < fixed_size; ++i) {
      accum[i] = accum[i - 1] + __builtin_popcountll(block[i - 1]);
    }
  }

  bool access(size_type idx) const {
    return block[idx / block_size] >> (idx & (block_size - 1)) & 1;
  }
  size_type rank(bool value, size_type idx) const {
    bit_type mask = (1ull << (idx & (block_size - 1))) - 1;
    size_type res = accum[idx / block_size] + __builtin_popcountll(block[idx / block_size] & mask);
    return value ? res : idx - res;
  }
  size_type select(bool value, size_type idx) const {
    if (idx >= rank(value, size)) {
      return size;
    }
    size_type ok = 0, ng = size;
    while (ng - ok > 1) {
      size_type md = (ok + ng) >> 1;
      (rank(value, md) <= idx ? ok : ng) = md;
    }
    return ok;
  }
  size_type select(bool value, size_type idx, size_type l) const {
    return select(value, idx + rank(value, l));
  }

};
