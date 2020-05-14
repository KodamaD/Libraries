
template <class T, class U = std::less<T>>
class li_chao_tree {
public:
  using value_type = T;
  using compare_type = U;
  using size_type = size_t;

  static constexpr compare_type compare{};
  static constexpr value_type max_inf = std::numeric_limits<value_type>::max();
  static constexpr value_type min_inf = std::numeric_limits<value_type>::min();
  static constexpr value_type identity = compare(min_inf, max_inf) ? max_inf : min_inf;

  struct line_type {
    value_type a, b;
    line_type(value_type a_ = 0, value_type b_ = identity): a(a_), b(b_) { }
    value_type operator () (value_type x) const { return a * x + b; }
  };

private:
  size_t M_size;
  std::vector<value_type> M_coordinate;
  std::vector<line_type> M_line;

  void M_add_line_impl(line_type line, size_type k, size_type l, size_type r) {
    size_type m = (l + r) >> 1;
    value_type x_l = M_coordinate[l];
    value_type x_m = M_coordinate[m];
    value_type x_r = M_coordinate[r];
    bool left = compare(line(x_l), M_line[k](x_l));
    bool mid = compare(line(x_m), M_line[k](x_m));
    bool right = compare(line(x_r), M_line[k](x_r));
    if (left && right) { M_line[k] = line; return; }
    if (!left && !right) return;
    if (mid) std::swap(line, M_line[k]);
    if (left != mid) M_add_line_impl(line, k << 1, l, m);
    else M_add_line_impl(line, k << 1 | 1, m + 1, r);
  }

public:
  li_chao_tree() = default;
  li_chao_tree(const std::vector<value_type> &coordinate_) { build(coordinate_); }

  void build(const std::vector<value_type> &coordinate_) {
    M_coordinate = coordinate_;
    M_size = 1;
    while (M_size < M_coordinate.size()) M_size <<= 1;
    value_type margin = M_coordinate.empty() ? 0 : M_coordinate.back();
    M_coordinate.resize(M_size, margin);
    M_line.assign(M_size << 1, line_type());
  }

  void add_line(line_type line) {
    M_add_line_impl(line, 1, 0, M_size - 1);
  }

  void add_segment(line_type line, value_type l, value_type r) {
    if (M_coordinate.front() > r) return;
    size_type i = std::lower_bound(M_coordinate.begin(), M_coordinate.end(), l) - M_coordinate.begin();
    size_type j = std::upper_bound(M_coordinate.begin(), M_coordinate.end(), r) - M_coordinate.begin();
    add_segment_compressed(line, i, j);
  }
  void add_segment_compressed(line_type line, size_type l, size_type r) {
    size_type cur_l = l, cur_r = r;
    size_type cur_size = 1;
    l += M_size;
    r += M_size;
    while (l < r) {
      if (l & 1) { 
        M_add_line_impl(line, l, cur_l, cur_l + cur_size - 1);
        ++l;
        cur_l += cur_size;
      }
      if (r & 1) {
        --r;
        cur_r -= cur_size;
        M_add_line_impl(line, r, cur_r, cur_r + cur_size - 1);
      }
      l >>= 1;
      r >>= 1;
      cur_size <<= 1;
    }
  }

  value_type get(value_type x) const {
    auto itr = std::lower_bound(M_coordinate.begin(), M_coordinate.end(), x);
    if (itr == M_coordinate.end() || x != *itr) return identity;
    return get_compressed(itr - M_coordinate.begin());
  }
  value_type get_compressed(size_type k) const {
    value_type x = M_coordinate[k];
    value_type res = identity;
    k += M_size;
    while (k > 0) {
      if (compare(M_line[k](x), res)) res = M_line[k](x);
      k >>= 1;
    }
    return res;
  }

};
