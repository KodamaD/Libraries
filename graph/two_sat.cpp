#pragma once

#include "../graph/network.cpp"
#include "../graph/scc.cpp"

#include <cstddef>
#include <utility>
#include <vector>
#include <cassert>

class two_sat {
public:
  using size_type = size_t;

private:
  network<base_edge> graph;

public:
  explicit two_sat() = default;
  explicit two_sat(const size_type size): graph(size * 2) { }

  void add_clause(const size_type i, const bool f, const size_type j, const bool g) {
    assert(i < size());
    assert(j < size());
    graph.emplace_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
    graph.emplace_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
  }

  std::pair<bool, std::vector<bool>> satisfy() const {
    const auto groups = strongly_connected_components(graph).decompose();
    std::vector<size_type> id(graph.size());
    std::vector<bool> res(size());
    for (size_type i = 0; i < groups.size(); ++i) {
      for (const auto x: groups[i]) {
        id[x] = i;
      }
    }
    for (size_type i = 0; i < size(); ++i) {
      if (id[2 * i] == id[2 * i + 1]) {
        return { false, { } };
      }
      res[i] = id[2 * i] < id[2 * i + 1];
    }
    return { true, res };
  }

  size_type size() const {
    return graph.size() / 2;
  }

};

/**
 * @title Two Sat
 */