
template <class T, std::size_t N, std::size_t I = 0>
decltype(auto) gen_vec(const std::size_t (&list)[N], typename std::enable_if<(I == N), const T&>::type value = T()) { 
  return value; 
}

template <class T, std::size_t N, std::size_t I = 0>
decltype(auto) gen_vec(const std::size_t (&list)[N], typename std::enable_if<(I != N), const T&>::type value = T()) { 
  return std::vector(list[I], gen_vec<T, N, I + 1>(list, value)); 
}
