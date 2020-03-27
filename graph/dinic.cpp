
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

template <class T>
class dinic {
public:
  using value_type = T;
  using size_type = int;

  struct edge_type {
    size_type to, rev;
    value_type cap;
  };

private:
  const value_type inf;
  size_type size;
  std::vector<std::vector<edge_type>> graph;
  std::vector<size_type> level, iter;

  void bfs(size_type start) {
    std::fill(level.begin(), level.end(), -1);
    std::queue<size_type> que;
    level[start] = 0;
    que.push(start);
    while (!que.empty()) {
      size_type u = que.front();
      que.pop();
      for (edge_type e: graph[u]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[u] + 1;
          que.push(e.to);
        }
      }
    }
  }

  value_type dfs(size_type cur, size_type goal, const value_type &flow) {
    if (cur == goal) return flow;
    for (size_type &i = iter[cur]; i < graph[cur].size(); ++i) {
      edge_type &e = graph[cur][i];
      if (e.cap > 0 && level[cur] < level[e.to]) {
        value_type tmp = dfs(e.to, goal, std::min(flow, e.cap));
        if (tmp > 0) {
          e.cap -= tmp;
          graph[e.to][e.rev].cap += tmp;
          return tmp;
        }
      }
    }
    return 0;
  }


public:
  dinic(): inf(std::numeric_limits<value_type>::max()) { }
  dinic(size_type size_): inf(std::numeric_limits<value_type>::max()) { init(size_); }

  void init(size_type size_) {
    size = size_;
    graph.assign(size_, { });
    level.assign(size_, -1);
    iter.assign(size_, 0);
  }

  void add_edge(size_type from, size_type to, const value_type &cap) {
    graph[from].push_back(edge_type{ to, (size_type) graph[to].size(), cap });
    graph[to].push_back(edge_type{ from, (size_type) graph[from].size() - 1, 0 });
  }

  value_type max_flow(size_type start, size_type goal) {
    value_type res = 0;
    while (true) {
      bfs(start);
      if (level[goal] == -1) return res;
      std::fill(iter.begin(), iter.end(), 0);
      value_type tmp;
      while ((tmp = dfs(start, goal, inf)) > 0) {
        res += tmp;
      }
    }
  }

};

int main() {
  return 0;
}
