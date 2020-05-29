
template <class T>
class lazy_propagation_segment_tree {
public:
  using value_type = typename T::value_type;
  using effector_type = typename T::effector_type;

  static inline const auto op1 = typename T::value_operation();
  static inline const auto op2 = typename T::effector_operation();
  static inline const auto op3 = typename T::merge_operation();

private:
  int size, height;
  std::vector<value_type> node;
  std::vector<effector_type> lazy;

  value_type fetch(int i, int l) const {
    if (lazy[i] == op2.identity) return node[i];
    return op3(node[i], lazy[i], l);
  }

  void apply(int i, int l) {
    if (lazy[i] == op2.identity) return;
    if (i < size) {
      lazy[i << 1 | 0] = op2(lazy[i << 1 | 0], lazy[i]);
      lazy[i << 1 | 1] = op2(lazy[i << 1 | 1], lazy[i]);
    }
    node[i] = op3(node[i], lazy[i], l);
    lazy[i] = op2.identity;
  }
  void update() {
    for (int i = size - 1; i > 0; --i) {
      node[i] = op1(node[i << 1 | 0], node[i << 1 | 1]);
    }
  }

  void flush(int i) {
    for (int k = height; k >= 0; --k) {
      apply(i >> k, 1 << k);
    }
  }
  void lift(int i) {
    i >>= 1;
    int l = 1;
    while (i > 0) {
      node[i] = op1(fetch(i << 1 | 0, l), fetch(i << 1 | 1, l));
      i >>= 1;
      l <<= 1;
    }
  }

public:
  lazy_propagation_segment_tree() = default;
  lazy_propagation_segment_tree(int size_, const value_type &initial_ = op1.identity) { init(size_, initial_); }
  lazy_propagation_segment_tree(const std::vector<value_type> &node_) { build(node_); }

  void init(int size_, const value_type &initial_ = op1.identity) {
    size = 1; 
    height = 0;
    while (size < size_) {
      size <<= 1;
      ++height;
    }
    node.assign(size << 1, initial_);
    lazy.assign(size << 1, op2.identity);
    update();
  }
  void build(const std::vector<value_type> &node_) {
    init(node_.size());
    for (int i = 0; i < node_.size(); ++i) {
      node[i + size] = node_[i];
    }
    update();
  }

  void assign(int i, const value_type &x) {
    i += size;
    flush(i);
    node[i] = x;
    lift(i);
  }

  void modify(int l, int r, const effector_type &x) {
    if (l >= r) return;
    flush(l + size);
    flush(r + size - 1);
    int tl = l + size, tr = r + size, k = 1;
    while (tl < tr) {
      if (tl & 1) {
        lazy[tl] = op2(lazy[tl], x);
        apply(tl, k);
        ++tl;
      }
      if (tr & 1) {
        --tr;
        lazy[tr] = op2(lazy[tr], x);
        apply(tr, k);
      }
      tl >>= 1;
      tr >>= 1;
      k <<= 1;
    }
    lift(l + size);
    lift(r + size - 1);
  }

  value_type fold(int l, int r) {
    if (l >= r) return op1.identity;
    flush(l + size);
    flush(r + size - 1);
    int tl = l + size, tr = r + size, k = 1;
    value_type resl = op1.identity, resr = op1.identity;
    while (tl < tr) {
      if (tl & 1) {
        apply(tl, k);
        resl = op1(resl, node[tl]);
        ++tl;
      }
      if (tr & 1) {
        --tr;
        apply(tr, k);
        resr = op1(node[tr], resr);
      }
      tl >>= 1;
      tr >>= 1;
      k <<= 1;
    }
    return op1(resl, resr);
  }

};
