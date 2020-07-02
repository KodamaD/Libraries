
template <class T, size_t N, size_t... Seq>
struct gen_arr_impl {
  using type = std::array<typename gen_arr_impl<T, Seq...>::type, N>;
};

template <class T, size_t N>
struct gen_arr_impl<T, N> {
  using type = std::array<T, N>;
};

template <class T, size_t N, size_t... Seq>
using gen_arr = typename gen_arr_impl<T, N, Seq...>::type; 
