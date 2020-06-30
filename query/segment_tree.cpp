
template <class Monoid>
class segment_tree {
public:
  using monoid     = Monoid;
  using value_type = typename Monoid::type;
  using size_type  = size_t;

private:
  std::vector<value_type> M_tree;

  void M_fix_change(const size_type index) {
    M_tree[index] = monoid::operation(M_tree[index << 1 | 0], M_tree[index << 1 | 1]);
  }

public:
  segment_tree() = default;
  explicit segment_tree(const size_type size) { initialize(size); }
  template <class InputIterator>
  explicit segment_tree(InputIterator first, InputIterator last) { construct(first, last); }

  void initialize(const size_type size) {
    clear();
    M_tree.assign(size << 1, monoid::identity());
  }

  template <class InputIterator>
  void construct(InputIterator first, InputIterator last) {
    clear();
    const size_type size = std::distance(first, last);
    M_tree.reserve(size << 1);
    M_tree.assign(size, monoid::identity());
    std::copy(first, last, std::back_inserter(M_tree));
    for (size_type index = size - 1; index != 0; --index) {
      M_fix_change(index);
    }
  }

  void assign(size_type index, const value_type &value) {
    index += size();
    M_tree[index] = value;
    while (index != 1) {
      index >>= 1;
      M_fix_change(index);
    } 
  }

  const value_type& at(size_type index) const { 
    return M_tree[index + size()];
  }

  value_type fold(size_type first, size_type last) const {
    first += size();
    last += size();
    value_type fold_l = monoid::identity();
    value_type fold_r = monoid::identity();
    while (first != last) {
      if (first & 1) {
        fold_l = monoid::operation(fold_l, M_tree[first]);
        ++first;
      }
      if (last & 1) {
        --last;
        fold_r = monoid::operation(M_tree[last], fold_r);      
      }
      first >>= 1;
      last  >>= 1;
    }
    return monoid::operation(fold_l, fold_r);
  }

  void clear() {
    M_tree.clear();
    M_tree.shrink_to_fit();
  }

  size_type size() const { 
    return M_tree.size() >> 1;
  }

};
