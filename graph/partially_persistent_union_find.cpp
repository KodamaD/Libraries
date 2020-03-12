
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

class partially_persistent_union_find {
private:
  const int inf;
  int size, last;
  std::vector<int> parent, updated, component;
  std::vector<std::vector<std::pair<int, int>>> history;

public:
  partially_persistent_union_find(): inf(std::numeric_limits<int>::max()) { }
  partially_persistent_union_find(int size_): inf(std::numeric_limits<int>::max()) {
    size = size_;
    last = -1;
    parent.assign(size_, 1);
    updated.assign(size_, inf);
    component.assign(1, size_);
    history.assign(size_, { { -1, 1 } });
  }

  int find_parent(int x, int t) const {
    if (updated[x] > t) {
      return x;
    }
    return find_parent(parent[x], t);
  }
  int when(int x, int y) const {
    if (!same_component(x, y, last)) {
      return inf;
    }
    int ok = last, ng = -1, md;
    while (ok - ng > 1) {
      md = (ok + ng) / 2;
      (same_component(x, y, md) ? ok : ng) = md;
    }
    return ok;
  }

  int count_components(int t) const {
    return component[std::min(t, last) + 1];
  }
  int component_size(int x, int t) const {
    x = find_parent(x, t);
    return (--std::upper_bound(history[x].begin(), history[x].end(), std::make_pair(t, inf ))) -> second;
  }

  bool same_component(int x, int y, int t) const {
    return find_parent(x, t) == find_parent(y, t);
  }
  bool unite(int x, int y) {
    x = find_parent(x, last);
    y = find_parent(y, last);
    int tmp_size = component.size();
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

int main() {
  return 0;
}