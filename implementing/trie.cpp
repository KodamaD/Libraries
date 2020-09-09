#pragma once

#include <cstddef>
#include <vector>
#include <iterator>
#include <map>
#include <array>

template <class Node>
class trie_impl {
public:
  using size_type = size_t;
  using value_type = typename Node::value_type;

protected:
  using node_type = Node;

  std::vector<node_type> M_tree;

  size_type M_add_node() {
    const auto res = M_tree.size();
    M_tree.emplace_back();
    return res;
  }

public:
  explicit trie_impl() { M_add_node(); }

  template <class InputIterator>
  std::vector<size_type> insert(InputIterator first, InputIterator last) {
    std::vector<size_type> res;
    res.reserve(std::distance(first, last) + 1);
    res.push_back(0);
    size_type cur = 0;
    for (; first != last; ++first) {
      const auto &c = *first;
      if (~next(cur, c) == 0) {
        const auto new_node = M_add_node();
        M_tree[cur].emplace(c, new_node);
      }
      cur = next(cur, c);
      res.push_back(cur);
    }
    return res;
  }

  template <class InputIterator>
  std::vector<size_type> find_path(InputIterator first, InputIterator last) const {
    const size_type size = std::distance(first, last) + 1;
    std::vector<size_type> res;
    res.reserve(size);
    res.push_back(0);
    size_type cur = 0;
    for (; first != last; ++first) {
      cur = next(cur, *first);
      if (~cur == 0) {
        break;
      }
      res.push_back(cur);
    }
    res.resize(size, size_type(-1));
    return res;
  }

  size_type next(const size_type index, const value_type &value) const {
    return M_tree[index].next(value);
  }
  size_type size() const {
    return M_tree.size();
  }

};

template <class T>
class map_based_trie_node {
public:
  using value_type = T;
private:
  std::map<value_type, size_t> M_children;
public:
  explicit map_based_trie_node(): M_children() { }
  size_t next(const value_type &value) const {
    const auto itr = M_children.find(value);
    return (itr == M_children.end() ? size_t(-1) : itr -> second);
  }
  void emplace(const value_type &value, const size_t index) {
    M_children.emplace(value, index);
  }
};

template <class T, T MinValue, size_t Size>
class array_based_trie_node {
public:
  using value_type = T;
private:
  std::array<size_t, Size> M_children;
public:
  explicit array_based_trie_node() { M_children.fill(size_t(-1)); }
  size_t next(const value_type &value) const {
    return M_children[value - MinValue];
  }
  void emplace(const value_type &value, const size_t index) {
    M_children[value - MinValue] = index;
  }
};

template <class T>
using trie_any = trie_impl<map_based_trie_node<T>>;

template <class T, T MinValue, size_t Size>
using trie_alphabet = trie_impl<array_based_trie_node<T, MinValue, Size>>;
