
#include <utility>

template <class T>
struct fix_point: private T {
  explicit constexpr fix_point(T &&func): T(std::forward<T>(func)) { }
  template <class... Args>
  constexpr decltype(auto) operator () (Args &&... args) const {
    return T::operator()(*this, std::forward<Args>(args)...);
  }
};

template <class T>
constexpr decltype(auto) make_fix_point(T &&func) {
  return fix_point<T>{std::forward<T>(func)};
}

int main() {
  return 0;
}