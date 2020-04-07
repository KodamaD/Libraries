
template <class T>
struct fix_point: private T {
  explicit constexpr fix_point(T &&func): T(std::forward<T>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return T::operator()(*this, std::forward<Args>(args)...);
  }
};
