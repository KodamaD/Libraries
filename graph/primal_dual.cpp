
template <class T>
class primal_dual {
public:
  using value_type = T;
  using size_type = size_t;
  using pair = std::pair<value_type, size_type>;

  static constexpr value_type inf = std::numeric_limits<value_type>::max();

  struct edge_type {
    size_type to, rev;
    value_type cap, cost;
  };

private:
  size_type size;
  std::vector<std::vector<edge_type>> graph;
  std::vector<value_type> dist, potential;
  std::vector<size_type> prev_v, prev_e;

  inline bool chmin(value_type &lhs, const value_type &rhs) const {
    if (lhs > rhs) {
      lhs = rhs;
      return true;
    }
    return false;
  }

public:
  primal_dual() { }
  primal_dual(size_type size_) { init(size_); }

  void init(size_type size_) {
    size = size_;
    graph.assign(size_, { });
    dist.assign(size_, 0);
    potential.assign(size_, 0);
    prev_v.assign(size_, 0);
    prev_e.assign(size_, 0);
  }

  void add_edge(size_type from, size_type to, value_type cap, value_type cost) {
    graph[from].push_back(edge_type{ to, (size_type) graph[to].size(), cap, cost });
    graph[to].push_back(edge_type{ from, (size_type) graph[from].size() - 1, 0, -cost });
  }

  value_type min_cost_flow(size_type start, size_type goal, value_type flow) {
    value_type res = 0;
    while (flow > 0) {
      std::fill(dist.begin(), dist.end(), inf);
      std::priority_queue<pair, std::vector<pair>, std::greater<pair>> que;
      dist[start] = 0;
      que.emplace(dist[start], start);
      while (!que.empty()) {
        auto [d, u] = que.top();
        que.pop();
        if (d > dist[u]) {
          continue;
        }
        for (size_type i = 0; i < graph[u].size(); ++i) {
          auto &e = graph[u][i];
          if (e.cap > 0 && chmin(dist[e.to], dist[u] + e.cost + potential[u] - potential[e.to])) {
            que.emplace(dist[e.to], e.to);
            prev_v[e.to] = u;
            prev_e[e.to] = i;
          }
        }
      }
      if (dist[goal] >= inf) {
        return inf;
      }
      for (size_type i = 0; i < size; ++i) {
        potential[i] += dist[i];
      }
      value_type use = flow;
      for (size_type u = goal; u != start; u = prev_v[u]) {
        chmin(use, graph[prev_v[u]][prev_e[u]].cap);
      }
      flow -= use;
      res += use * potential[goal];
      for (size_type u = goal; u != start; u = prev_v[u]) {
        auto &e = graph[prev_v[u]][prev_e[u]];
        e.cap -= use;
        graph[u][e.rev].cap += use;
      }
    }
    return res;
  }

};
