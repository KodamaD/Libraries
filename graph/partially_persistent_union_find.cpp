#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>
#include <algorithm>

class partially_persistent_union_find {
public:
  using size_type = int32_t;
  static constexpr size_type inf = std::numeric_limits<size_type>::max();

private:
  size_type size, last;
  std::vector<size_type> parent, updated, component;
  std::vector<std::vector<std::pair<size_type, size_type>>> history;

public:
  partially_persistent_union_find() = default;
  partially_persistent_union_find(size_type size_) {
    size = size_;
    last = -1;
    parent.assign(size_, 1);
    updated.assign(size_, inf);
    component.assign(1, size_);
    history.assign(size_, { { -1, 1 } });
  }

  size_type find_parent(size_type x, size_type t) const {
    if (updated[x] > t) {
      return x;
    }
    return find_parent(parent[x], t);
  }
  size_type when(size_type x, size_type y) const {
    if (!same_component(x, y, last)) {
      return inf;
    }
    size_type ok = last, ng = -1, md;
    while (ok - ng > 1) {
      md = (ok + ng) / 2;
      (same_component(x, y, md) ? ok : ng) = md;
    }
    return ok;
  }

  size_type count_components(size_type t) const {
    return component[std::min(t, last) + 1];
  }
  size_type component_size(size_type x, size_type t) const {
    x = find_parent(x, t);
    return (--std::upper_bound(history[x].begin(), history[x].end(), std::make_pair(t, inf ))) -> second;
  }

  bool same_component(size_type x, size_type y, size_type t) const {
    return find_parent(x, t) == find_parent(y, t);
  }
  bool unite(size_type x, size_type y) {
    x = find_parent(x, last);
    y = find_parent(y, last);
    size_type tmp_size = component.size();
    ++last;
    if (x == y) {
      component.push_back(tmp_size);
      return false;
    }
    if (parent[x] < parent[y]) {
      std::swap(x, y);
    }
    parent[x] += parent[y];
    parent[y] = x;
    updated[y] = last;
    component.push_back(tmp_size - 1);
    history[x].emplace_back(last, parent[x]);
    return true;
  }

};
