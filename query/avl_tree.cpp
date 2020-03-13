
#include <algorithm>

template <class T>
class avl_tree {
public:
  struct node_type;
  using node_ptr = node_type *;
  using value_type = T;
  using size_type = int;

  struct node_type {
    node_ptr left, right;
    value_type value;
    size_type size, height;
  };

private:
  node_ptr M_root;
  size_type M_node_count;

  inline size_type size(node_ptr node) const {
    return node ? node -> size : 0;
  }
  inline size_type height(node_ptr node) const {
    return node ? node -> height : 0;
  }
  inline size_type coeff(node_ptr node) const {
    return node ? height(node -> left) - height(node -> right) : 0;
  }

  inline node_ptr apply(node_ptr node) {
    node -> size = size(node -> left) + size(node -> right) + 1;
    node -> height = std::max(height(node -> left), height(node -> right)) + 1;
    return node;
  }
  inline node_ptr rotate_l(node_ptr node) {
    node_ptr new_root = node -> right;
    node -> right = new_root -> left;
    new_root -> left = node;
    return apply(node), apply(new_root);
  }
  inline node_ptr rotate_r(node_ptr node) {
    node_ptr new_root = node -> left;
    node -> left = new_root -> right;
    new_root -> right = node;
    return apply(node), apply(new_root);
  }
  inline node_ptr balance(node_ptr node) {
    size_type dif = coeff(apply(node));
    if (dif == 2) {
      if (coeff(node -> left) < 0) node -> left = rotate_l(node -> left);
      return rotate_r(node);
    } 
    if (dif == -2) {
      if (coeff(node -> right) > 0) node -> right = rotate_r(node -> right);
      return rotate_l(node);
    } 
    return node;
  }

  node_ptr M_insert_impl(node_ptr node, const value_type &val) {
    if (!node) return new node_type{ nullptr, nullptr, val, 1, 1 };
    if (val < node -> value) node -> left = M_insert_impl(node -> left, val);
    else node -> right = M_insert_impl(node -> right, val);
    return balance(node);
  }
  node_ptr M_erase_impl(node_ptr node, const value_type &val) {
    if (!node) return nullptr;
    if (val < node -> value) node -> left = M_erase_impl(node -> left, val);
    else if (val > node -> value) node -> right = M_erase_impl(node -> right, val);
    else {
      if (!(node -> left) || !(node -> right)) {
        --M_node_count;
        node_ptr res = node -> left ? node -> left : node -> right;
        delete node;
        return res;
      }
      node_ptr right_end = node -> left;
      while (right_end -> right) right_end = right_end -> right;
      node -> value = right_end -> value;
      node -> left = M_erase_impl(node -> left, right_end -> value);
    }
    return balance(node);
  }
  void M_clear_impl(node_ptr node) {
    if (!node) return;
    M_clear_impl(node -> left);
    M_clear_impl(node -> right);
    delete node;
  }

public:
  avl_tree():
    M_root(nullptr),
    M_node_count(0)
  { }
  ~avl_tree() {
    M_clear_impl(M_root);
  }

  void insert(const value_type &val) {
    M_root = M_insert_impl(M_root, val);
    ++M_node_count;
  }
  void erase(const value_type &val) {
    M_root = M_erase_impl(M_root, val);
  }
  void clear() {
    M_clear_impl(M_root);
  }

  bool empty() const {
    return M_node_count == 0;
  }
  bool contains(const value_type &val) const {
    node_ptr cur = M_root;
    while (cur) {
      if (val == cur -> value) return true;
      if (val < cur -> value) cur = cur -> left;
      else cur = cur -> right;
    }
    return false;
  }

  size_type size() const {
    return M_node_count;
  }
  size_type lower_bound(const value_type &val) const {
    node_ptr cur = M_root;
    size_type cnt = 0;
    while (cur) {
      if (val <= cur -> value) cur = cur -> left;
      else cnt += size(cur -> left) + 1, cur = cur -> right;
    }
    return cnt;
  }
  size_type upper_bound(const value_type &val) const {
    node_ptr cur = M_root;
    size_type cnt = 0;
    while (cur) {
      if (val < cur -> value) cur = cur -> left;
      else cnt += size(cur -> left) + 1, cur = cur -> right;
    }
    return cnt;
  }

  value_type at(size_type idx) const {
    node_ptr cur = M_root;
    size_type cnt = 0;
    while (true) {
      if (cnt + size(cur -> left) == idx) return cur -> value;
      else if (cnt + size(cur -> left) > idx) cur = cur -> left;
      else cnt += size(cur -> left) + 1, cur = cur -> right;
    }
  }

};


int main() {
  return 0;
}
