---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: graph/link_cut_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/link_cut_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-07 09:00:40+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/link_cut_tree.cpp"

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

