#pragma once

#include <cstddef>
#include <vector>
#include <utility>

class union_find {
public:
  using size_type = size_t;

private:
  class node_type {
  public:
    size_type parent, size;
    node_type(size_type parent, size_type size): 
      parent(parent), size(size) 
    { }
  };

  size_type M_components;
  std::vector<node_type> M_forest;

public:
  union_find() = default;
  explicit union_find(size_type size) { initialize(size); }

  void initialize(size_type size) {
    clear();
    M_components = size;
    M_forest.reserve(size);
    for (size_type index = 0; index < size; ++index) {
      M_forest.emplace_back(index, 1);
    }
  }

  size_type find_parent(size_type node) {
    size_type &parent = M_forest[node].parent;
    if (node == parent) return node;
    return parent = find_parent(parent);
  }
  size_type count_components() const { 
    return M_components; 
  }
  size_type component_size(size_type node) { 
    return M_forest[find_parent(node)].size;
  }

  bool unite(size_type node1, size_type node2) {
    node1 = find_parent(node1);
    node2 = find_parent(node2);
    if (node1 == node2) return false;
    if (M_forest[node1].size < M_forest[node2].size) {
      std::swap(node1, node2);
    }
    M_forest[node1].size += M_forest[node2].size;
    M_forest[node2].parent = node1;
    --M_components;
    return true;
  }
  bool same_component(size_type node1, size_type node2) { 
    return find_parent(node1) == find_parent(node2); 
  }

  size_type size() const {
    return M_forest.size();
  }
  bool empty() const {
    return M_forest.empty();
  }
  void clear() {
    M_components = 0;
    M_forest.clear();
    M_forest.shrink_to_fit();
  }

};

/**
 * @title Union Find
 */