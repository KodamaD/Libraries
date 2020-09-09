#pragma once

#include "trie.cpp"

template <class Trie>
class aho_corasick_impl: public Trie {
public:
  using value_type = typename Trie::value_type;
  using size_type = typename Trie::size_type;

private:
  std::vector<size_type> link;

public:

  void construct() {
    
  }

};

template <class T>
using aho_corasick_any = aho_corasick_impl<trie_any<T>>;

template <class T, T MinValue, size_t Size>
using aho_corasick_alphabet = aho_corasick_impl<trie_alphabet<T, MinValue, Size>>;

#include <iostream>

int main() {
  aho_corasick_any<char> a;
  std::cout << a.size() << '\n';
}
