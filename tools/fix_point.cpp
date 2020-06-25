
template <class Func>
struct fix_point: private Func {
  explicit constexpr fix_point(Func &&func): Func(std::forward<Func>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return T::operator()(*this, std::forward<Args>(args)...);
  }
};
