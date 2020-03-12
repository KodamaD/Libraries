
#include <vector>
#include <utility>

class heavy_light_decomposition {
private:
  std::vector<std::vector<int>> graph;
  std::vector<int> size, parent, head;
  int index;

  void calc_size(int u, int p) {
    size[u] = 1;
    for (int v: graph[u]) {
      if (v != p) {
        calc_size(v, u);
        size[u] += size[v];
      }
    }
  }

  void decompose(int u, int p, int h) {
    label[u] = index;
    head[u] = h;
    parent[u] = p;
    ++index;
    int max = -1, heavy = -1;
    for (int v : graph[u]) {
      if (v != p) {
        if (max < size[v]) {
          max = size[v];
          heavy = v;
        }
      }
    }
    if (heavy == -1) {
      return;
    }
    decompose(heavy, u, h);
    for (int v : graph[u]) {
      if (v != p && v != heavy) {
        decompose(v, u, v);
      }
    }
  }

public:
  std::vector<int> label;

  heavy_light_decomposition() { }
  heavy_light_decomposition(int size_) { init(size_); }

  void init(int size_) {
    graph.assign(size_, { });
    size.assign(size_, 0);
    parent.assign(size_, 0);
    head.assign(size_, 0);
    label.assign(size_, 0);
  }

  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  void build() {
    index = 0;
    calc_size(0, -1);
    decompose(0, -1, 0);
  }

  template <class T> 
  void each_edge(int u, int v, const T &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (head[u] == head[v]) {
        if (label[u] + 1 <= label[v]) {
          func(label[u] + 1, label[v]);
        }
        return;
      }
      func(label[head[v]], label[v]);
      v = parent[head[v]];
    }
  }

  template <class T> 
  void each_vertex(int u, int v, const T &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (head[u] == head[v]) {
        func(label[u], label[v]);
        return;
      }
      func(label[head[v]], label[v]);
      v = parent[head[v]];
    }
  }

  int lca(int u, int v) const {
    if (label[u] > label[v]) {
      std::swap(u, v);
    }
    while (label[u] <= label[v]) {
      if (head[u] == head[v]) {
        return u;
      }
      v = parent[head[v]];
    }
    return v;
  }

};

int main() {
  return 0;
}
