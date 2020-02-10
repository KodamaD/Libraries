
#include <vector>

template <class T>
class fenwick {
public:
  using value_type = T;

private:
  int size;
  std::vector<value_type> node;

public:
  fenwick() = default;
  fenwick(int size_) { init(size_); }

  void init(int size_) {
    size = size_;
    node.assign(size_ + 1, 0);
  }

  void modify(int i, const value_type& x) {
    ++i;
    while (i <= size) {
      node[i] += x;
      i += i & -i;
    }
  }

  value_type get(int i) const {
    ++i;
    value_type res = 0;
    while (i > 0) {
      res += node[i];
      i -= i & -i;
    }
    return res;
  }
  value_type fold(int l, int r) const {
    return get(r - 1) - get(l - 1);
  }

};

int main() {
  return 0;
}