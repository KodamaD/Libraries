
template <class T>
class segment_tree_beats {
public:
  using value_type = T;
  using size_type = size_t;

  static constexpr value_type inf = std::numeric_limits<value_type>::max();

private:
  size_type size;
  size_type query_l, query_r;
  value_type query_v;
  std::vector<value_type> sum, lazy;
  std::vector<value_type> max, max2, cnt_max;
  std::vector<value_type> min, min2, cnt_min;

  void update_node_max(size_type k, const value_type &val) {
    sum[k] += (val - max[k]) * cnt_max[k];
    if (max[k] == min[k]) min[k] = val;
    else if (min2[k] == max[k]) min2[k] = val;
    max[k] = val;
  }
  void update_node_min(size_type k, const value_type &val) {
    sum[k] += (val - min[k]) * cnt_min[k];
    if (min[k] == max[k]) max[k] = val;
    else if (max2[k] == min[k]) max2[k] = val;
    min[k] = val;
  }
  void update_node_add(size_type k, size_type len, const value_type &val) {
    max[k] += val;
    if (max2[k] != -inf) max2[k] += val;
    min[k] += val;
    if (min2[k] != inf) min2[k] += val;
    sum[k] += val * len;
    lazy[k] += val;
  }

  void flush(size_type k, size_type len) {
    if (k >= size) return;
    if (lazy[k] != 0) {
      update_node_add(k << 1 | 0, len >> 1, lazy[k]);
      update_node_add(k << 1 | 1, len >> 1, lazy[k]);
      lazy[k] = 0;
    }
    if (max[k << 1 | 0] > max[k]) update_node_max(k << 1 | 0, max[k]);
    if (min[k << 1 | 0] < min[k]) update_node_min(k << 1 | 0, min[k]);
    if (max[k << 1 | 1] > max[k]) update_node_max(k << 1 | 1, max[k]);
    if (min[k << 1 | 1] < min[k]) update_node_min(k << 1 | 1, min[k]);
  }
  void apply(size_type k) {
    sum[k] = sum[k << 1 | 0] + sum[k << 1 | 1];
    if (max[k << 1 | 0] > max[k << 1 | 1]) {
      max[k] = max[k << 1 | 0];
      max2[k] = std::max(max2[k << 1 | 0], max[k << 1 | 1]);
      cnt_max[k] = cnt_max[k << 1 | 0];
    }
    else if (max[k << 1 | 1] > max[k << 1 | 0]) {
      max[k] = max[k << 1 | 1];
      max2[k] = std::max(max2[k << 1 | 1], max[k << 1 | 0]);
      cnt_max[k] = cnt_max[k << 1 | 1];
    }
    else {
      max[k] = max[k << 1 | 0];
      max2[k] = std::max(max2[k << 1 | 0], max2[k << 1 | 1]);
      cnt_max[k] = cnt_max[k << 1 | 0] + cnt_max[k << 1 | 1];
    }
    if (min[k << 1 | 0] < min[k << 1 | 1]) {
      min[k] = min[k << 1 | 0];
      min2[k] = std::min(min2[k << 1 | 0], min[k << 1 | 1]);
      cnt_min[k] = cnt_min[k << 1 | 0];
    }
    else if (min[k << 1 | 1] < min[k << 1 | 0]) {
      min[k] = min[k << 1 | 1];
      min2[k] = std::min(min2[k << 1 | 1], min[k << 1 | 0]);
      cnt_min[k] = cnt_min[k << 1 | 1];
    }
    else {
      min[k] = min[k << 1 | 0];
      min2[k] = std::min(min2[k << 1 | 0], min2[k << 1 | 1]);
      cnt_min[k] = cnt_min[k << 1 | 0] + cnt_min[k << 1 | 1];  
    }
  }

  void M_chmin_impl(size_type l, size_type r, size_type k) {
    if (l >= query_r || r <= query_l || query_v >= max[k]) return;
    if (query_l <= l && r <= query_r && max2[k] < query_v) {
      update_node_max(k, query_v);
      return;
    }
    flush(k, r - l);
    M_chmin_impl(l, (l + r) >> 1, k << 1 | 0);
    M_chmin_impl((l + r) >> 1, r, k << 1 | 1);
    apply(k);
  }
  void M_chmax_impl(size_type l, size_type r, size_type k) {
    if (l >= query_r || r <= query_l || query_v <= min[k]) return;
    if (query_l <= l && r <= query_r && min2[k] > query_v) {
      update_node_min(k, query_v);
      return;
    }
    flush(k, r - l);
    M_chmax_impl(l, (l + r) >> 1, k << 1 | 0);
    M_chmax_impl((l + r) >> 1, r, k << 1 | 1);
    apply(k);
  }
  void M_add_impl(size_type l, size_type r, size_type k) {
    if (l >= query_r || r <= query_l) return;
    if (query_l <= l && r <= query_r) {
      update_node_add(k, r - l, query_v);
      return;
    }
    flush(k, r - l);
    M_add_impl(l, (l + r) >> 1, k << 1 | 0);
    M_add_impl((l + r) >> 1, r, k << 1 | 1);
    apply(k);
  }

  value_type M_max_impl(size_type l, size_type r, size_type k) {
    if (l >= query_r || r <= query_l) return -inf;
    if (query_l <= l && r <= query_r) return max[k];
    flush(k, r - l);
    return std::max(M_max_impl(l, (l + r) >> 1, k << 1 | 0), M_max_impl((l + r) >> 1, r, k << 1 | 1));
  }
  value_type M_min_impl(size_type l, size_type r, size_type k) {
    if (l >= query_r || r <= query_l) return -inf;
    if (query_l <= l && r <= query_r) return min[k];
    flush(k, r - l);
    return std::min(M_min_impl(l, (l + r) >> 1, k << 1 | 0), M_min_impl((l + r) >> 1, r, k << 1 | 1));
  }
  value_type M_sum_impl(size_type l, size_type r, size_type k) {
    if (l >= query_r || r <= query_l) return 0;
    if (query_l <= l && r <= query_r) return sum[k];
    flush(k, r - l);
    return M_sum_impl(l, (l + r) >> 1, k << 1 | 0) + M_sum_impl((l + r) >> 1, r, k << 1 | 1);
  }
  
public:
  segment_tree_beats(size_type size_, const value_type &initial_) { init(size_, initial_); }
  segment_tree_beats(const std::vector<value_type> &node_) { build(node_); }

  void init(size_type size_, const value_type &initial_) {
    size = (size_ > 0 ? 1 << (31 - __builtin_clz(2 * size_ - 1)) : 1);
    sum.assign(size << 1, initial_);
    lazy.assign(size << 1, 0);
    max.assign(size << 1, initial_);
    max2.assign(size << 1, -inf);
    cnt_max.assign(size << 1, 1);
    min.assign(size << 1, initial_);
    min2.assign(size << 1, inf);
    cnt_min.assign(size << 1, 1);
    for (size_type i = size - 1; i > 0; --i) {
      apply(i);
    }
  }
  void build(const std::vector<value_type> &node_) {
    init(node_.size(), 0);
    for (size_type i = 0; i < node_.size(); ++i) {
      sum[i + size] = max[i + size] = min[i + size] = node_[i];
    }
    for (size_type i = size - 1; i > 0; --i) {
      apply(i);
    }
  }

  void chmax(size_type l, size_type r, const value_type &val) {
    if (l >= r) return;
    query_l = l;
    query_r = r;
    query_v = val;
    M_chmax_impl(0, size, 1);
  }
  void chmin(size_type l, size_type r, const value_type &val) {
    if (l >= r) return;
    query_l = l;
    query_r = r;
    query_v = val;
    M_chmin_impl(0, size, 1);
  }
  void add(size_type l, size_type r, const value_type &val) {
    if (l >= r) return;
    query_l = l;
    query_r = r;
    query_v = val;
    M_add_impl(0, size, 1);
  }

  value_type maximum(size_type l, size_type r) {
    if (l >= r) return -inf;
    query_l = l;
    query_r = r;
    return M_max_impl(0, size, 1);
  }
  value_type minimum(size_type l, size_type r) {
    if (l >= r) return inf;
    query_l = l;
    query_r = r;
    return M_min_impl(0, size, 1);
  }
  value_type accumulate(size_type l, size_type r) {
    if (l >= r) return 0;
    query_l = l;
    query_r = r;
    return M_sum_impl(0, size, 1);
  }

};
