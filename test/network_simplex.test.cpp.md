---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/network_simplex.cpp
    title: Network Simplex
  - icon: ':heavy_check_mark:'
    path: other/adjust_index.cpp
    title: Index Adjustment
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_cost_b_flow
    links:
    - https://judge.yosupo.jp/problem/min_cost_b_flow
  bundledCode: "#line 1 \"test/network_simplex.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\
    \n\n#line 2 \"graph/network_simplex.cpp\"\n\n#line 2 \"other/adjust_index.cpp\"\
    \n\n#include <cstddef>\n#include <cassert>\n\nclass adjust_index {\nprivate:\n\
    \  const size_t M_stuff, M_size;\n\npublic:\n  explicit adjust_index(const size_t\
    \ stuff, const size_t size): \n    M_stuff(stuff), M_size(size) \n  { }\n\n  size_t\
    \ operator [] (const size_t index) const {\n    assert(index < M_size);\n    return\
    \ M_stuff + index;\n  }\n  size_t to_index(const size_t fixed) const {\n    assert(fixed\
    \ >= M_stuff);\n    assert(fixed < M_size + M_stuff);\n    return fixed - M_stuff;\n\
    \  }\n  size_t size() const {\n    return M_size;\n  }\n};\n\n/**\n * @title Index\
    \ Adjustment\n */\n#line 4 \"graph/network_simplex.cpp\"\n\n#line 6 \"graph/network_simplex.cpp\"\
    \n#include <cstdint>\n#include <utility>\n#include <cmath>\n#include <vector>\n\
    #include <stack>\n#include <set>\n#include <type_traits>\n#line 14 \"graph/network_simplex.cpp\"\
    \n\ntemplate <class Flow, class Cost>\nclass network_simplex {\npublic:\n  using\
    \ flow_type = Flow;\n  using cost_type = Cost;\n  using size_type = size_t;\n\
    \  using node_id   = size_t;\n  using edge_id   = size_t;\n\n  static_assert(std::is_signed<flow_type>::value,\
    \ \"flow-type must be signed integer\");\n  static_assert(std::is_integral<flow_type>::value,\
    \ \"flow-type must be signed integer\");\n  static_assert(std::is_signed<cost_type>::value,\
    \ \"cost-type must be signed integer\");\n  static_assert(std::is_integral<cost_type>::value,\
    \ \"cost-type must be signed integer\");\n\n  struct return_type {\n  public:\n\
    \    const bool feasible;\n    const std::vector<cost_type> potentials;\n    const\
    \ std::vector<std::pair<flow_type, cost_type>> edges;\n\n    explicit return_type(\n\
    \      const bool feasible,\n      const std::vector<cost_type> potentials,\n\
    \      const std::vector<std::pair<flow_type, cost_type>> edges\n    ): feasible(feasible),\
    \ potentials(potentials), edges(edges) { }\n\n    template <class T>\n    T calculate()\
    \ const {\n      T res = 0;\n      for (const auto &e: edges) {\n        res +=\
    \ (T) e.first * e.second;\n      }\n      return res;\n    }\n  };\n\nprivate:\n\
    \  class edge_type {\n  public:\n    const node_id src, dst;\n    flow_type flow;\n\
    \    const flow_type capacity;\n    const cost_type cost;\n\n    explicit edge_type(\n\
    \      const node_id src, const node_id dst,\n      const flow_type flow, const\
    \ flow_type capacity,\n      const cost_type cost\n    ): src(src), dst(dst),\
    \ flow(flow), capacity(capacity), cost(cost) { }\n  };\n\n  class node_type {\n\
    \  public:\n    flow_type balance;\n    cost_type potential;\n    std::set<edge_id>\
    \ tree_edges;\n    size_type depth;\n    edge_id parent_edge;\n\n    explicit\
    \ node_type(const flow_type balance = 0):\n      balance(balance), potential(0),\
    \ tree_edges(), depth(0), parent_edge(-1)\n    { }\n  };\n\n  std::vector<edge_type>\
    \ edges;\n  std::vector<node_type> nodes;\n\n  static edge_id rev_id(const edge_id\
    \ eid) {\n    return (eid ^ 1);\n  }\n  template <class T>\n  static bool minimize(T\
    \ &current, const T &new_cost) {\n    if (current > new_cost) { current = new_cost;\
    \ return true; }\n    return false;\n  }\n\n  flow_type residual_capacity(const\
    \ edge_id eid) const {\n    return edges[eid].capacity - edges[eid].flow;\n  }\n\
    \  cost_type reduced_cost(const edge_id eid) const {\n    return edges[eid].cost\
    \ + nodes[edges[eid].src].potential - nodes[edges[eid].dst].potential;\n  }\n\
    \  bool send_flow(const edge_id eid, const flow_type flow) {\n    edges[eid].flow\
    \ += flow;\n    edges[rev_id(eid)].flow -= flow;\n    return edges[eid].flow ==\
    \ edges[eid].capacity;\n  }\n\n  void precompute() {\n    cost_type inf_cost =\
    \ 1;\n    for (const auto &e: edges) {\n      if (e.cost > 0) inf_cost += e.cost;\n\
    \    }\n    const auto root = add_node();\n    for (node_id nid = 0; nid != root;\
    \ ++nid) {\n      const auto flow = nodes[nid].balance;\n      if (flow < 0) {\n\
    \        const auto eid = add_edge(root, nid, (flow_type) 0, -flow, inf_cost)\
    \ << 1;\n        send_flow(eid, -flow);\n        nodes[root].tree_edges.insert(eid);\n\
    \        nodes[nid].tree_edges.insert(rev_id(eid));\n      }\n      else {\n \
    \       const auto eid = add_edge(nid, root, (flow_type) 0, flow + 1, inf_cost)\
    \ << 1;\n        send_flow(eid, flow);\n        nodes[nid].tree_edges.insert(eid);\n\
    \        nodes[root].tree_edges.insert(rev_id(eid));\n      }\n    }\n    evert(root);\n\
    \  }\n\n  void evert(const node_id root) {\n    std::stack<node_id> stack;\n \
    \   stack.push(root);\n    while (!stack.empty()) {\n      const auto nid = stack.top();\n\
    \      stack.pop();\n      for (const auto eid: nodes[nid].tree_edges) {\n   \
    \     if (eid != nodes[nid].parent_edge) {\n          const auto dst = edges[eid].dst;\n\
    \          nodes[dst].potential = nodes[nid].potential + edges[eid].cost;\n  \
    \        nodes[dst].depth = nodes[nid].depth + 1;\n          nodes[dst].parent_edge\
    \ = rev_id(eid);\n          stack.push(dst);\n        }\n      }\n    }\n  }\n\
    \n  edge_id select_edge() {\n    static const size_type block_size = (size_type)\
    \ std::sqrt(edges.size());\n    static size_type edge_scan = 0;\n    static const\
    \ auto advance = [&] {\n      if (++edge_scan == edges.size()) edge_scan = 0;\n\
    \    };\n    size_type step = 0;\n    while (step < edges.size()) {\n      cost_type\
    \ optimal_cost = 0;\n      edge_id select = -1;\n      for (size_type minor =\
    \ 0; minor != block_size; ++minor) {\n        if (step == edges.size()) break;\n\
    \        const edge_id eid = edge_scan;\n        advance();\n        ++step;\n\
    \        if (residual_capacity(eid) > 0) {\n          if (minimize(optimal_cost,\
    \ reduced_cost(eid))) select = eid;\n        }\n      }\n      if (~select) return\
    \ select;\n    }\n    return (edge_id) -1;\n  }\n\n  void pivot(const edge_id\
    \ eid) {\n    flow_type send = residual_capacity(eid);\n    auto src_side = edges[eid].src;\n\
    \    auto dst_side = edges[eid].dst;\n    while (src_side != dst_side) {\n   \
    \   if (nodes[src_side].depth > nodes[dst_side].depth) {\n        const auto down_edge\
    \ = rev_id(nodes[src_side].parent_edge);\n        minimize(send, residual_capacity(down_edge));\n\
    \        src_side = edges[down_edge].src;\n      }\n      else {\n        const\
    \ auto up_edge = nodes[dst_side].parent_edge;\n        minimize(send, residual_capacity(up_edge));\n\
    \        dst_side = edges[up_edge].dst;\n      }\n    }\n    const auto lca =\
    \ src_side;\n    edge_id remove = -1;\n    enum leaving_arc { SRC, DST, ENT };\n\
    \    leaving_arc state = ENT;\n    src_side = edges[eid].src;\n    while (src_side\
    \ != lca) {\n      const auto down_edge = rev_id(nodes[src_side].parent_edge);\n\
    \      if (send_flow(down_edge, send)) {\n        if (~remove == 0) {\n      \
    \    remove = down_edge;\n          state = SRC;\n        }\n      }\n      src_side\
    \ = edges[down_edge].src;\n    }\n    if (send_flow(eid, send)) {\n      remove\
    \ = eid;\n      state = ENT;\n    }\n    dst_side = edges[eid].dst;\n    while\
    \ (dst_side != lca) {\n      const auto up_edge = nodes[dst_side].parent_edge;\n\
    \      if (send_flow(up_edge, send)) {\n        remove = up_edge;\n        state\
    \ = DST;\n      }\n      dst_side = edges[up_edge].dst;\n    }\n    if (state\
    \ == ENT) return;\n    nodes[edges[eid].src].tree_edges.insert(eid);\n    nodes[edges[eid].dst].tree_edges.insert(rev_id(eid));\n\
    \    nodes[edges[remove].src].tree_edges.erase(remove);\n    nodes[edges[remove].dst].tree_edges.erase(rev_id(remove));\n\
    \    evert(state == SRC ? edges[eid].dst : edges[eid].src);\n  }\n\npublic:\n\
    \  explicit network_simplex() = default;\n  explicit network_simplex(const size_type\
    \ size) {\n    add_nodes(size);\n  }\n\n  node_id add_node(const flow_type balance\
    \ = 0) {\n    const node_id res = nodes.size();\n    nodes.emplace_back(balance);\n\
    \    return res;\n  }\n  adjust_index add_nodes(const size_type size) {\n    const\
    \ size_type cur = nodes.size();\n    nodes.resize(cur + size);\n    return adjust_index(cur,\
    \ size);\n  }\n\n  void add_supply(const node_id node, const flow_type supply)\
    \ {\n    assert(node < nodes.size());\n    nodes[node].balance += supply;\n  }\n\
    \  void add_demand(const node_id node, const flow_type demand) {\n    assert(node\
    \ < nodes.size());\n    nodes[node].balance -= demand;\n  }\n   \n  edge_id add_edge(\n\
    \    const node_id src, const node_id dst, \n    const flow_type lower_bound,\
    \ const flow_type upper_bound,\n    const cost_type cost\n  ) {\n    assert(src\
    \ < nodes.size());\n    assert(dst < nodes.size());\n    assert(lower_bound <=\
    \ upper_bound);\n    const edge_id res = edges.size() >> 1;\n    edges.emplace_back(src,\
    \ dst, lower_bound, upper_bound, cost);\n    edges.emplace_back(dst, src, -lower_bound,\
    \ -lower_bound, -cost);\n    if (lower_bound != (flow_type) 0) {\n      add_demand(src,\
    \ lower_bound);\n      add_supply(dst, lower_bound);\n    }\n    return res;\n\
    \  }\n\n  return_type solve() {\n    precompute();\n    edge_id select = select_edge();\n\
    \    while (~select) {\n      pivot(select);\n      select = select_edge();\n\
    \    }\n    bool feasible = true;\n    const auto split = edges.size() - 2 * (nodes.size()\
    \ - 1);\n    for (edge_id eid = split; eid != edges.size(); ++eid) {\n      if\
    \ (edges[eid].flow > 0) {\n        feasible = false;\n        break;\n      }\n\
    \    }\n    std::vector<cost_type> pt(nodes.size() - 1);\n    for (node_id nid\
    \ = 0; nid != nodes.size() - 1; ++nid) {\n      pt[nid] = nodes[nid].potential;\n\
    \    }\n    std::vector<std::pair<flow_type, cost_type>> es;\n    es.reserve(split\
    \ >> 1);\n    for (edge_id eid = 0; eid != split; eid += 2) {\n      es.emplace_back(edges[eid].flow,\
    \ edges[eid].cost);\n    }\n    return return_type(feasible, pt, es);\n  }\n\n\
    };\n\n/**\n * @title Network Simplex\n */\n#line 5 \"test/network_simplex.test.cpp\"\
    \n\n#line 8 \"test/network_simplex.test.cpp\"\n#include <string>\n#include <iostream>\n\
    #include <algorithm>\n\nstd::string to_str(__int128_t x) {\n  if (x == 0) {\n\
    \    return \"0\";\n  }\n  std::string s;\n  bool neg = false;\n  if (x < 0) {\n\
    \    x = -x;\n    neg = true;\n  }\n  while (x > 0) {\n    s += '0' + x % 10;\n\
    \    x /= 10;\n  }\n  if (neg) {\n    s += '-';\n  }\n  std::reverse(s.begin(),\
    \ s.end());\n  return s;\n}\n\nint main() {\n  size_t N, M;\n  std::cin >> N >>\
    \ M;\n  network_simplex<int64_t, int64_t> net(N);\n  for (size_t i = 0; i < N;\
    \ ++i) {\n    int64_t p;\n    std::cin >> p;\n    net.add_supply(i, p);\n  }\n\
    \  for (size_t i = 0; i < M; ++i) {\n    size_t s, t;\n    int64_t l, u, c;\n\
    \    std::cin >> s >> t >> l >> u >> c;\n    net.add_edge(s, t, l, u, c);\n  }\n\
    \  const auto ans = net.solve();\n  if (ans.feasible) {\n    std::cout << to_str(ans.calculate<__int128_t>())\
    \ << '\\n';\n    for (const auto p: ans.potentials) {\n      std::cout << p <<\
    \ '\\n';\n    }\n    for (const auto [f, c]: ans.edges) {\n      std::cout <<\
    \ f << '\\n';\n    }\n  }\n  else {\n    std::cout << \"infeasible\\n\";\n  }\n\
    \  return 0;\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n\n\
    #include \"../graph/network_simplex.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <string>\n#include <iostream>\n#include <algorithm>\n\nstd::string to_str(__int128_t\
    \ x) {\n  if (x == 0) {\n    return \"0\";\n  }\n  std::string s;\n  bool neg\
    \ = false;\n  if (x < 0) {\n    x = -x;\n    neg = true;\n  }\n  while (x > 0)\
    \ {\n    s += '0' + x % 10;\n    x /= 10;\n  }\n  if (neg) {\n    s += '-';\n\
    \  }\n  std::reverse(s.begin(), s.end());\n  return s;\n}\n\nint main() {\n  size_t\
    \ N, M;\n  std::cin >> N >> M;\n  network_simplex<int64_t, int64_t> net(N);\n\
    \  for (size_t i = 0; i < N; ++i) {\n    int64_t p;\n    std::cin >> p;\n    net.add_supply(i,\
    \ p);\n  }\n  for (size_t i = 0; i < M; ++i) {\n    size_t s, t;\n    int64_t\
    \ l, u, c;\n    std::cin >> s >> t >> l >> u >> c;\n    net.add_edge(s, t, l,\
    \ u, c);\n  }\n  const auto ans = net.solve();\n  if (ans.feasible) {\n    std::cout\
    \ << to_str(ans.calculate<__int128_t>()) << '\\n';\n    for (const auto p: ans.potentials)\
    \ {\n      std::cout << p << '\\n';\n    }\n    for (const auto [f, c]: ans.edges)\
    \ {\n      std::cout << f << '\\n';\n    }\n  }\n  else {\n    std::cout << \"\
    infeasible\\n\";\n  }\n  return 0;\n}\n"
  dependsOn:
  - graph/network_simplex.cpp
  - other/adjust_index.cpp
  isVerificationFile: true
  path: test/network_simplex.test.cpp
  requiredBy: []
  timestamp: '2020-09-21 19:57:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/network_simplex.test.cpp
layout: document
redirect_from:
- /verify/test/network_simplex.test.cpp
- /verify/test/network_simplex.test.cpp.html
title: test/network_simplex.test.cpp
---
