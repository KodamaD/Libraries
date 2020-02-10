
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

template <class T>
class network {
public:
  using value_type = T;

private:
  struct edge {
    int to, rev; value_type cap;
    edge(int to_,  int rev_, value_type cap_) 
      : to(to_), rev(rev_), cap(cap_) 
    { }
  };
  int size;
  std::vector<std::vector<edge>> graph;
  std::vector<int> level, iter;

  void bfs(int start) {
    fill(level.begin(), level.end(), -1);
    level[start] = 0;
    std::queue<int> que;
    que.push(start);
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (edge e : graph[v]) {
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          que.push(e.to);
        }
      }
    }
  }

  value_type dfs(int now, int goal, value_type flow) {
    if (now == goal) {
      return flow;
    }
    for (int& i = iter[now]; i < graph[now].size(); ++i) {
      edge& e = graph[now][i];
      if (e.cap > 0 && level[now] < level[e.to]) {
        value_type tmp = dfs(e.to, goal, std::min<value_type>(flow, e.cap));
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
  network() { }
  network(int size_) { init(size_); }

  void init(int size_) {
    size = size_;
    graph.assign(size_, { });
    level.assign(size_, 0);
    iter.assign(size_, 0);
  }

  void add_edge(int from, int to, value_type cap) {
    graph[from].emplace_back(to, graph[to].size(), cap);
    graph[to].emplace_back(from, graph[from].size() - 1, 0);
  }

  value_type dinic(int start, int goal) {
    value_type flow = 0;
    while (true) {
      bfs(start);
      if (level[goal] < 0) {
        return flow;
      }
      std::fill(iter.begin(), iter.end(), 0);
      value_type tmp;
      while ((tmp = dfs(start, goal, std::numeric_limits<value_type>::max())) > 0) {
        flow += tmp;
      }
    }
  }
 
};

int main() {
  return 0;
}