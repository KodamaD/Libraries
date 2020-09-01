
#include "../other/fix_point.cpp"

#include <cstdint>
#include <memory>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <initializer_list>
#include <stdexcept>

#include <iostream>
#include <cassert>

template <class T>
class sequence {
public:
  using value_type  = T;
  using size_type   = uint32_t;
 
private:
  class node_type;
  using height_type = int8_t;
  using root_type   = std::unique_ptr<node_type>;

  class node_type {
  public:
    node_type *parent;
    std::pair<root_type, root_type> children;

    value_type value;
    size_type size;
    height_type height;
    bool reversed;

    node_type(const value_type& value):
      parent(nullptr), children(),
      value(value), size(1), height(1), reversed(false)
    { }
    template <class... Args>
    node_type(Args&&... args):
      parent(nullptr), children(),
      value(std::forward<Args>(args)...), size(1), height(1), reversed(false)
    { }
  };

  class node_ref {
  private:
    node_type *ptr;

  public:
    explicit node_ref(const root_type &root): ptr(root.get()) { }
    node_type* operator -> () const { return ptr; }

    void ascend() { ptr = ptr -> parent; }
    template <bool Side>
    void descend() { ptr = std::get<Side>(ptr -> children).get(); }

    bool select(size_type &index) {
      const size_type left_size = size(std::get<0>(ptr -> children));
      if (index == left_size) return false;
      if (index < left_size) descend<0>();
      else index -= (left_size + 1), descend<1>();
      return true;
    }
  };
 
  template <bool Side>
  static root_type &child(root_type &rt) {
    return std::get<Side>(rt -> children);
  }
  template <bool Side>
  static const root_type &child(const root_type &rt) {
    return std::get<Side>(rt -> children);
  }
  static size_type size(const root_type &rt) { 
    return rt ? rt -> size : 0;
  }
  static height_type height(const root_type &rt) { 
    return rt ? rt -> height : 0;
  }
  static height_type coeff(const root_type &rt) { 
    return rt ? height(child<0>(rt)) - height(child<1>(rt)) : 0; 
  }
 
  static void fix_change(root_type &rt) {
    rt -> size = size(child<0>(rt)) + 1 + size(child<1>(rt));
    rt -> height = std::max(height(child<0>(rt)), height(child<1>(rt))) + 1;
  }
  template <bool Side>
  static void set_child(root_type &rt, root_type ch) {
    if (ch) ch -> parent = rt.get();
    child<Side>(rt) = std::move(ch);
  }
  template <bool Side>
  static void rotate(root_type &rt) {
    root_type new_rt = std::move(child<!Side>(rt));
    new_rt -> parent = rt -> parent;
    set_child<!Side>(rt, std::move(child<Side>(new_rt))); fix_change(rt);
    set_child<Side>(new_rt, std::move(rt)); fix_change(new_rt);
    rt = std::move(new_rt);
  }
  static void balance(root_type &rt) {
    const height_type diff = coeff(rt);
    if (diff == 2) {
      if (coeff(child<0>(rt)) < 0) rotate<0>(child<0>(rt));
      rotate<1>(rt);
    }
    if (diff == -2) {
      if (coeff(child<1>(rt)) > 0) rotate<1>(child<1>(rt));
      rotate<0>(rt);
    }
  }

  static void extract_rightmost(root_type &rt, root_type &result) {
    if (!child<1>(rt)) {
      result = std::move(rt);
      if (child<0>(result)) {
        rt = std::move(child<0>(result));
        fix_change(result);
      }
      return;
    }
    extract_rightmost(child<1>(rt), result);
    fix_change(rt);
    balance(rt);
  }
  static void absorb_sides(root_type left, root_type &rt, root_type right) {
    const height_type diff = height(left) - height(right);
    if (-1 <= diff && diff <= 1) {
      set_child<0>(rt, std::move(left));
      set_child<1>(rt, std::move(right));
      fix_change(rt);
      return;
    }
    if (diff > 0) {
      absorb_sides(std::move(child<1>(left)), rt, std::move(right));
      set_child<1>(left, std::move(rt));
      rt = std::move(left);
    }
    else {
      absorb_sides(std::move(left), rt, std::move(child<0>(right)));
      set_child<0>(right, std::move(rt));
      rt = std::move(right);
    }
    fix_change(rt);
    balance(rt);
  }

  static void insert(root_type &rt, root_type target, const size_type index) {
    if (!rt) { rt = std::move(target); return; }
    const size_type left_size = size(child<0>(rt));
    if (index <= left_size) insert(child<0>(rt), std::move(target), index);
    else insert(child<1>(rt), std::move(target), index - left_size - 1);
    fix_change(rt);
    balance(rt);
  }
  static void erase(root_type &rt, const size_type index) {
    const size_type left_size = size(child<0>(rt));
    if (index == left_size) {
      if (!child<0>(rt)) { rt = std::move(child<1>(rt)); return; } 
      if (!child<1>(rt)) { rt = std::move(child<0>(rt)); return; }
      root_type new_rt;
      extract_rightmost(child<0>(rt), new_rt);
      set_child<0>(new_rt, std::move(child<0>(rt)));
      set_child<1>(new_rt, std::move(child<1>(rt)));
      rt = std::move(new_rt);
    }
    else if (index < left_size) erase(child<0>(rt), index);
    else erase(child<1>(rt), index - left_size - 1);
    fix_change(rt);
    balance(rt);
  }

  static root_type merge(root_type left, root_type right) {
    if (!left) return right;
    if (!right) return left;
    root_type rt;
    extract_rightmost(left, rt);
    absorb_sides(std::move(left), rt, std::move(right));
    return rt;
  }
  static std::pair<root_type, root_type> split(root_type rt, const size_type index) {
    if (!rt) return { nullptr, nullptr };
    root_type left = std::move(child<0>(rt));
    root_type right = std::move(child<1>(rt));
    fix_change(rt);
    const size_type left_size = size(left);
    if (index == left_size) {
      insert(right, std::move(rt), 0);
      return std::make_pair(std::move(left), std::move(right));
    }
    else if (index < left_size) {
      auto tmp = split(std::move(left), index);
      absorb_sides(std::move(std::get<1>(tmp)), rt, std::move(right));
      return std::make_pair(std::move(std::get<0>(tmp)), std::move(rt));
    }
    else {
      auto tmp = split(std::move(right), index - left_size - 1);
      absorb_sides(std::move(left), rt, std::move(std::get<0>(tmp)));
      return std::make_pair(std::move(rt), std::move(std::get<1>(tmp)));
    }
  }

  static root_type build(const std::vector<value_type> &vec) {
    return fix_point([&](auto dfs, const size_type left, const size_type right) -> root_type {
      const size_type mid = (left + right) >> 1;
      root_type rt = std::make_unique<node_type>(std::move(vec[mid]));
      if (left != mid) set_child<0>(rt, dfs(left, mid));
      if (mid + 1 != right) set_child<1>(rt, dfs(mid + 1, right));
      fix_change(rt);
      return rt;
    })(0, vec.size());
  }
  static root_type copy(const root_type &rt) {
    root_type new_rt = std::make_unique<node_type>(rt -> value);
    new_rt -> reversed = rt -> reversed;
    if (child<0>(rt)) set_child<0>(new_rt, copy(child<0>(rt)));
    if (child<1>(rt)) set_child<1>(new_rt, copy(child<1>(rt)));
    fix_change(new_rt);
    return new_rt;
  }

  sequence &remove_const() const { 
    return const_cast<sequence&>(*this); 
  }

  root_type root;

public:
  explicit sequence(): root() { }
  explicit sequence(const size_type size, const value_type &value = value_type{ }): 
    root(build(std::vector<value_type>(size, value)))
  { }
  template <class InputIt>
  explicit sequence(InputIt first, InputIt last): 
    root(build(std::vector<value_type>(first, last)))
  { }
  sequence(std::initializer_list<value_type> list): 
    root(build(std::vector<value_type>(list.begin(), list.end())))
  { }
  sequence(const sequence &seq): root(copy(seq.root)) { }
  sequence(sequence &&seq) noexcept: root(std::move(seq.root)) { }

  sequence& operator = (const sequence &seq) {
    if (this != &seq) root = copy(seq.root);
    return *this;
  }
  sequence& operator = (sequence &&seq) noexcept {
    if (this != &seq) root = std::move(seq.root);
    return *this;
  }
  sequence& operator = (std::initializer_list<value_type> list) {
    root = build(std::vector<value_type>(list.begin(), list.end()));
    return *this;
  }

  void assign(const size_type size, const value_type &value = value_type{ }) {
    *this = sequence(size, value);
  }
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    *this = sequence(first, last);
  }
  void assign(std::initializer_list<value_type> list) {
    *this = sequence(list.begin(), list.end());
  }

  value_type &operator [] (size_type index) {
    node_ref pos(root);
    while (pos.select(index));
    return pos -> value;
  }
  value_type &at(size_type index) {
    if (index < size()) return (*this)[index];
    throw std::out_of_range("called `sequence::at` with invalid index");
  }
  const value_type &operator [] (size_type index) const {
    return remove_const()[index];
  }
  const value_type &at(size_type index) const {
    return remove_const().at(index);
  }

  size_type size() const noexcept {
    return size(root);
  }
  bool empty() const noexcept {
    return static_cast<bool>(root);
  }
};

int main() {
  sequence<int> seq = { 1, 1, 4, 5, 1, 4 };
  auto seq2 = seq;
  for (size_t i = 0; i < seq.size(); ++i) {
    std::cout << seq[i] << ' ';
  }
  std::cout << '\n';
  for (size_t i = 0; i < seq2.size(); ++i) {
    std::cout << seq2[i] << ' ';
  }
  std::cout << '\n';
  const auto seq3 = std::move(seq2);
  for (size_t i = 0; i < seq2.size(); ++i) {
    std::cout << seq2.at(i) << ' ';
  }
  std::cout << '\n';
  for (size_t i = 0; i < seq3.size(); ++i) {
    std::cout << seq3.at(i) << ' ';
  }
  std::cout << '\n';
  return 0;
}
