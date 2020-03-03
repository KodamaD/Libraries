
#include <vector>

template <class T>
class segment_tree {
public:
  using value_type = typename T::value_type;
  using effector_type = typename T::effector_type;
  using value_operation = typename T::value_operation;
  using merge_operation = typename T::merge_operation;

private:
  int size;
  const value_operation op1;
  const merge_operation op2;
  std::vector<value_type> node;

  void update() {
    for (int k = size - 1; k > 0; --k) {
      node[k] = op1(node[k << 1 | 0], node[k << 1 | 1]);
    }
  }

public:
  segment_tree(): op1(value_operation()), op2(merge_operation()) { }
  segment_tree(int size_, const value_type &initial_ = value_operation().identity):
    op1(value_operation()), op2(merge_operation())
  { init(size_, initial_); }
  segment_tree(const std::vector<value_type> &node_):
    op1(value_operation()), op2(merge_operation())
  { build(node_); }

  void init(int size_, const value_type &initial_ = value_operation().identity) {
    size = 1;
    while (size < size_) {
      size <<= 1;
    }
    node.assign(size << 1, initial_);
    update();
  }
  void build(const std::vector<value_type> &node_) {
    init(node_.size());
    assign(node_.begin(), node_.end(), 0);
  }

  void modify(int i, const effector_type &x) {
    i += size;
    node[i] = op2(node[i], x);
    while (i > 1) {
      i >>= 1;
      node[i] = op1(node[i << 1 | 0], node[i << 1 | 1]);
    }
  }
  template <class U>
  void modify(U begin, U end, int i) {
    i += size;
    while (begin != end) {
      node[i] = op2(node[i], *begin);
      ++i;
      ++begin;
    }
    update();
  }

  void assign(int i, const value_type &x) {
    i += size;
    node[i] = x;
    while (i > 1) {
      i >>= 1;
      node[i] = op1(node[i << 1 | 0], node[i << 1 | 1]);
    } 
  }
  template <class U>
  void assign(U begin, U end, int i) {
    i += size;
    while (begin != end) {
      node[i] = *begin;
      ++i;
      ++begin;
    }
    update();
  }

  value_type operator [] (int i) const { 
    return node[i + size];
  }
  value_type fold(int l, int r) const {
    l += size;
    r += size;
    value_type resl = op1.identity;
    value_type resr = op1.identity;
    while (l < r) {
      if (l & 1) {
        resl = op1(resl, node[l++]);
      }
      if (r & 1) {
        resr = op1(node[--r], resr);
      }
      l >>= 1;
      r >>= 1;
    }
    return op1(resl, resr);
  }

};

int main() {
  return 0;
}
