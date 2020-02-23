
#include <type_traits>
#include <vector>

template <class T, int N, int I = 0>
auto gen_vec(const int (&list)[N], typename std::enable_if<(I == N), const T&>::type value = T()) { 
  return value; 
}

template <class T, int N, int I = 0>
auto gen_vec(const int (&list)[N], typename std::enable_if<(I != N), const T&>::type value = T()) { 
  return std::vector<decltype(gen_vec<T, N, I + 1>(list, value))>(list[I], gen_vec<T, N, I + 1>(list, value)); 
}

int main() {
  return 0;
}