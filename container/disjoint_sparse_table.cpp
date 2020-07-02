
template <class T>
class disjoint_sparse_table {
public:
  using value_type = typename T::value_type;
  static inline const auto op = typename T::value_operation();

private:
  std::vector<std::vector<value_type>> table;

public: 
  disjoint_sparse_table() = default;
  disjoint_sparse_table(const std::vector<value_type> &table_) { build(table_); }

  void build(const std::vector<value_type> &table_) {
    int height = 0, size = table_.size();
    while ((1 << height) < size) ++height;
    if (size == 1) ++height;
    table.assign(height, std::vector<value_type>(size));
    for (int i = 0; i < size; ++i) {
      table[0][i] = table_[i];
    }
    for (int i = 1; i < height; ++i) {
      int bit = (1 << i);
      for (int l = 0; l < size; l += (bit << 1)) {
        int m = (l + bit < size ? l + bit : size);
        table[i][m - 1] = table_[m - 1];
        for (int j = m - 2; j >= l; --j) {
          table[i][j] = op(table_[j], table[i][j + 1]);
        }
        if (m >= size) continue;
        int r = (m + bit < size ? m + bit : size);
        table[i][m] = table_[m];
        for (int j = m + 1; j < r; ++j) {
          table[i][j] = op(table[i][j - 1], table_[j]);
        }
      }
    }
  }

  value_type fold(int l, int r) const {
    if (l >= --r) return table[0][l];
    int h = 31 - __builtin_clz(l ^ r);
    return op(table[h][l], table[h][r]);
  }

};
