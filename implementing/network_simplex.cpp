#pragma once

#include <cstddef>
#include <cstdint>

template <class Flow, class Cost>
class network_simplex {
public:
  using flow_type = Flow;
  using cost_type = Cost;
  using size_type = size_t;

  class edge_type {
  public:
    const size_type src;
    const size_type dest;
    flow_type flow;
    const flow_type capacity;
    const cost_type cost;

    explicit edge_type(const size_type src, const size_type dest,
      const flow_type flow, const flow_type capacity, const cost_type cost):
      src(src), dest(dest), flow(flow), capacity(capacity), cost(cost) { }
  };

private:
  std::vector<edge_type> edges;
  
public:



};

/**
 * @title Network Simplex
 */