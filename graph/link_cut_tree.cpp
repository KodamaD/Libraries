
#include <algorithm>

class link_cut_tree {
public:
  struct node_type;
  using root_type = node_type *;

  struct node_type {
    int idx;
    root_type parent, left, right;
    bool is_root() const {
      return !parent || (parent -> left != this && parent -> right != this);
    }
    void rotate_l() {
      root_type x = parent;
      root_type y = x -> parent;
      if (x -> right = left) {
        left -> parent = x;
      }
      left = x;
      x -> parent = this;
      if (parent = y) {
        if (y -> left == x) y -> left = this;
        if (y -> right == x) y -> right = this;
      }
    }
    void rotate_r() {
      root_type x = parent;
      root_type y = x -> parent;
      if (x -> left = right) {
        right -> parent = x;
      }
      right = x;
      x -> parent = this;
      if (parent = y) {
        if (y -> left == x) y -> left = this;
        if (y -> right == x) y -> right = this;
      }
    }
    void splay() {
      while (!is_root()) {
        root_type x = parent;
        if (x -> is_root()) {
          if (x -> left == this) rotate_r();
          else rotate_l();
        }
        else {
          root_type y = x -> parent;
          if (y -> left == x) {
            if (x -> left == this) { x -> rotate_r(); rotate_r(); }
            else { rotate_l(); rotate_r(); }
          }
          else {
            if (x -> right == this) { x -> rotate_l(); rotate_l(); }
            else { rotate_r(); rotate_l(); }
          }
        }
      }
    }
  };

private:
  std::vector<root_type> vertices;

  root_type expose(root_type node) const {
    root_type last = nullptr;
    for (root_type cur = node; cur; cur = cur -> parent) {
      cur -> splay();
      cur -> right = last;
      last = cur;
    }
    node -> splay();
    return last;
  }

  root_type root(root_type node) const {
    expose(node);
    while (node -> left) node = node -> left;
    return node;
  }
  root_type lca(root_type x, root_type y) const {
    if (root(x) != root(y)) return nullptr;
    return expose(x), expose(y);
  }

  void link(root_type child, root_type parent) const {
    expose(child);
    expose(parent);
    child -> parent = parent;
    parent -> right = child;
  }
  void cut(root_type child) const {
    expose(child);
    root_type tmp = child -> left;
    child -> left = nullptr;
    tmp -> parent = nullptr;
  }

public:
  link_cut_tree() { }
  link_cut_tree(int size_) {
    vertices.assign(size_, nullptr);
    for (int i = 0; i < size_; ++i) {
      vertices[i] = new node_type{ i, nullptr, nullptr, nullptr };
    }
  }
  ~link_cut_tree() {
    for (auto x: vertices) {
      delete x;
    }
  }

  void link(int x, int y) {
    link(vertices[x], vertices[y]);
  }
  void cut(int x) {
    cut(vertices[x]);
  }

  int root(int x) {
    return root(vertices[x]) -> idx;
  }
  int lca(int x, int y) {
    root_type tmp = lca(vertices[x], vertices[y]);
    return tmp ? tmp -> idx : -1;
  }

};

int main() {
  return 0;
}
