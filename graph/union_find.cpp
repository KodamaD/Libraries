#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>

class union_find {
private:
  size_t component;
  std::vector<int32_t> parent;

public:
  union_find() = default;
  union_find(size_t size_) { init(size_); }

  void init(size_t size_) {
    component = size_;
    parent.assign(size_, -1);
  }

  size_t count_components() const { 
    return component; 
  }
  size_t component_size(size_t i) { 
    return -parent[find_parent(i)]; 
  }
  bool same_component(size_t i, size_t j) { 
    return find_parent(i) == find_parent(j); 
  }

  size_t find_parent(size_t i) {
    if (parent[i] < 0) {
      return i;
    }
    else {
      return parent[i] = find_parent(parent[i]);
    }
  }

  bool unite(size_t i, size_t j) {
    i = find_parent(i);
    j = find_parent(j);
    if (i == j) {
      return false;
    }
    if (parent[i] > parent[j]) {
      std::swap(i, j);
    }
    parent[i] += parent[j];
    parent[j] = i;
    --component;
    return true;
  }

};
