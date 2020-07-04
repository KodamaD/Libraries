#pragma once

#include <cstddef>
#include <array>

template <class T, size_t N, size_t... Seq>
struct multi_array_impl {
  using type = std::array<typename multi_array_impl<T, Seq...>::type, N>;
};

template <class T, size_t N>
struct multi_array_impl<T, N> {
  using type = std::array<T, N>;
};

template <class T, size_t N, size_t... Seq>
using multi_array = typename multi_array_impl<T, N, Seq...>::type; 
