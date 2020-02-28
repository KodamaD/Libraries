
#include <vector>
#include <utility>

class union_find {
private:
  int component;
  std::vector<int> parent;

public:
  union_find() = default;
  union_find(int size_) { init(size_); }

  void init(int size_) {
    component = size_;
    parent.assign(size_, -1);
  }

  int count_components() const { 
    return component; 
  }
  int component_size(int i) { 
    return -parent[find_parent(i)]; 
  }
  bool same_component(int i, int j) { 
    return find_parent(i) == find_parent(j); 
  }

  int find_parent(int i) {
    if (parent[i] < 0) {
      return i;
    }
    else {
      return parent[i] = find_parent(parent[i]);
    }
  }

  bool unite(int i, int j) {
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

int main() {
  return 0;
}