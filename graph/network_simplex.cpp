#pragma once

#include "../other/adjust_index.cpp"

#include <cstddef>
#include <cstdint>
#include <utility>
#include <cmath>
#include <vector>
#include <stack>
#include <set>
#include <type_traits>
#include <cassert>

template <class Flow, class Cost>
class network_simplex {
public:
  using flow_type = Flow;
  using cost_type = Cost;
  using size_type = size_t;
  using node_id   = size_t;
  using edge_id   = size_t;

  static_assert(std::is_signed<flow_type>::value, "flow-type must be signed integer");
  static_assert(std::is_integral<flow_type>::value, "flow-type must be signed integer");
  static_assert(std::is_signed<cost_type>::value, "cost-type must be signed integer");
  static_assert(std::is_integral<cost_type>::value, "cost-type must be signed integer");

  struct return_type {
  public:
    const bool feasible;
    const std::vector<cost_type> potentials;
    const std::vector<std::pair<flow_type, cost_type>> edges;

    explicit return_type(
      const bool feasible,
      const std::vector<cost_type> potentials,
      const std::vector<std::pair<flow_type, cost_type>> edges
    ): feasible(feasible), potentials(potentials), edges(edges) { }

    template <class T>
    T calculate() const {
      T res = 0;
      for (const auto &e: edges) {
        res += (T) e.first * e.second;
      }
      return res;
    }
  };

private:
  class edge_type {
  public:
    const node_id src, dst;
    flow_type flow;
    const flow_type capacity;
    const cost_type cost;

    explicit edge_type(
      const node_id src, const node_id dst,
      const flow_type flow, const flow_type capacity,
      const cost_type cost
    ): src(src), dst(dst), flow(flow), capacity(capacity), cost(cost) { }
  };

  class node_type {
  public:
    flow_type balance;
    cost_type potential;
    std::set<edge_id> tree_edges;
    size_type depth;
    edge_id parent_edge;

    explicit node_type(const flow_type balance = 0):
      balance(balance), potential(0), tree_edges(), depth(0), parent_edge(-1)
    { }
  };

  std::vector<edge_type> edges;
  std::vector<node_type> nodes;

  static edge_id rev_id(const edge_id eid) {
    return (eid ^ 1);
  }
  template <class T>
  static bool minimize(T &current, const T &new_cost) {
    if (current > new_cost) { current = new_cost; return true; }
    return false;
  }

  flow_type residual_capacity(const edge_id eid) const {
    return edges[eid].capacity - edges[eid].flow;
  }
  cost_type reduced_cost(const edge_id eid) const {
    return edges[eid].cost + nodes[edges[eid].src].potential - nodes[edges[eid].dst].potential;
  }
  bool send_flow(const edge_id eid, const flow_type flow) {
    edges[eid].flow += flow;
    edges[rev_id(eid)].flow -= flow;
    return edges[eid].flow == edges[eid].capacity;
  }

  void precompute() {
    cost_type inf_cost = 1;
    for (const auto &e: edges) {
      if (e.cost > 0) inf_cost += e.cost;
    }
    const auto root = add_node();
    for (node_id nid = 0; nid != root; ++nid) {
      const auto flow = nodes[nid].balance;
      if (flow < 0) {
        const auto eid = add_edge(root, nid, (flow_type) 0, -flow, inf_cost) << 1;
        send_flow(eid, -flow);
        nodes[root].tree_edges.insert(eid);
        nodes[nid].tree_edges.insert(rev_id(eid));
      }
      else {
        const auto eid = add_edge(nid, root, (flow_type) 0, flow + 1, inf_cost) << 1;
        send_flow(eid, flow);
        nodes[nid].tree_edges.insert(eid);
        nodes[root].tree_edges.insert(rev_id(eid));
      }
    }
    evert(root);
  }

  void evert(const node_id root) {
    std::stack<node_id> stack;
    stack.push(root);
    while (!stack.empty()) {
      const auto nid = stack.top();
      stack.pop();
      for (const auto eid: nodes[nid].tree_edges) {
        if (eid != nodes[nid].parent_edge) {
          const auto dst = edges[eid].dst;
          nodes[dst].potential = nodes[nid].potential + edges[eid].cost;
          nodes[dst].depth = nodes[nid].depth + 1;
          nodes[dst].parent_edge = rev_id(eid);
          stack.push(dst);
        }
      }
    }
  }

  edge_id select_edge() {
    static const size_type block_size = (size_type) std::sqrt(edges.size());
    static size_type edge_scan = 0;
    static const auto advance = [&] {
      if (++edge_scan == edges.size()) edge_scan = 0;
    };
    size_type step = 0;
    while (step < edges.size()) {
      cost_type optimal_cost = 0;
      edge_id select = -1;
      for (size_type minor = 0; minor != block_size; ++minor) {
        if (step == edges.size()) break;
        const edge_id eid = edge_scan;
        advance();
        ++step;
        if (residual_capacity(eid) > 0) {
          if (minimize(optimal_cost, reduced_cost(eid))) select = eid;
        }
      }
      if (~select) return select;
    }
    return (edge_id) -1;
  }

  void pivot(const edge_id eid) {
    flow_type send = residual_capacity(eid);
    auto src_side = edges[eid].src;
    auto dst_side = edges[eid].dst;
    while (src_side != dst_side) {
      if (nodes[src_side].depth > nodes[dst_side].depth) {
        const auto down_edge = rev_id(nodes[src_side].parent_edge);
        minimize(send, residual_capacity(down_edge));
        src_side = edges[down_edge].src;
      }
      else {
        const auto up_edge = nodes[dst_side].parent_edge;
        minimize(send, residual_capacity(up_edge));
        dst_side = edges[up_edge].dst;
      }
    }
    const auto lca = src_side;
    edge_id remove = -1;
    enum leaving_arc { SRC, DST, ENT };
    leaving_arc state = ENT;
    src_side = edges[eid].src;
    while (src_side != lca) {
      const auto down_edge = rev_id(nodes[src_side].parent_edge);
      if (send_flow(down_edge, send)) {
        if (~remove == 0) {
          remove = down_edge;
          state = SRC;
        }
      }
      src_side = edges[down_edge].src;
    }
    if (send_flow(eid, send)) {
      remove = eid;
      state = ENT;
    }
    dst_side = edges[eid].dst;
    while (dst_side != lca) {
      const auto up_edge = nodes[dst_side].parent_edge;
      if (send_flow(up_edge, send)) {
        remove = up_edge;
        state = DST;
      }
      dst_side = edges[up_edge].dst;
    }
    if (state == ENT) return;
    nodes[edges[eid].src].tree_edges.insert(eid);
    nodes[edges[eid].dst].tree_edges.insert(rev_id(eid));
    nodes[edges[remove].src].tree_edges.erase(remove);
    nodes[edges[remove].dst].tree_edges.erase(rev_id(remove));
    evert(state == SRC ? edges[eid].dst : edges[eid].src);
  }

public:
  explicit network_simplex() = default;
  explicit network_simplex(const size_type size) {
    add_nodes(size);
  }

  node_id add_node(const flow_type balance = 0) {
    const node_id res = nodes.size();
    nodes.emplace_back(balance);
    return res;
  }
  adjust_index add_nodes(const size_type size) {
    const size_type cur = nodes.size();
    nodes.resize(cur + size);
    return adjust_index(cur, size);
  }

  void add_supply(const node_id node, const flow_type supply) {
    assert(node < nodes.size());
    nodes[node].balance += supply;
  }
  void add_demand(const node_id node, const flow_type demand) {
    assert(node < nodes.size());
    nodes[node].balance -= demand;
  }
   
  edge_id add_edge(
    const node_id src, const node_id dst, 
    const flow_type lower_bound, const flow_type upper_bound,
    const cost_type cost
  ) {
    assert(src < nodes.size());
    assert(dst < nodes.size());
    assert(lower_bound <= upper_bound);
    const edge_id res = edges.size() >> 1;
    edges.emplace_back(src, dst, lower_bound, upper_bound, cost);
    edges.emplace_back(dst, src, -lower_bound, -lower_bound, -cost);
    if (lower_bound != (flow_type) 0) {
      add_demand(src, lower_bound);
      add_supply(dst, lower_bound);
    }
    return res;
  }

  return_type solve() {
    precompute();
    edge_id select = select_edge();
    while (~select) {
      pivot(select);
      select = select_edge();
    }
    bool feasible = true;
    const auto split = edges.size() - 2 * (nodes.size() - 1);
    for (edge_id eid = split; eid != edges.size(); ++eid) {
      if (edges[eid].flow > 0) {
        feasible = false;
        break;
      }
    }
    std::vector<cost_type> pt(nodes.size() - 1);
    for (node_id nid = 0; nid != nodes.size() - 1; ++nid) {
      pt[nid] = nodes[nid].potential;
    }
    std::vector<std::pair<flow_type, cost_type>> es;
    es.reserve(split >> 1);
    for (edge_id eid = 0; eid != split; eid += 2) {
      es.emplace_back(edges[eid].flow, edges[eid].cost);
    }
    return return_type(feasible, pt, es);
  }

};

/**
 * @title Network Simplex
 */