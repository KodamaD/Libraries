
#include <ctime>
#include <type_traits>

class random_number {
public:
  using random_type = unsigned long long;
  using large_type = long long;
  using small_type = long double;

  template <class T, class U>
  using fixed_type = typename std::common_type<T, U>::type;

private:
  large_type fix_large;
  small_type fix_small;

  inline random_type engine() const {
    static random_type current = std::clock() ^ std::time(nullptr);
    current ^= current << 13;
    current ^= current >> 17;
    current ^= current << 5;
    return current;
  }

public:
  random_number() { setprecision(10); }

  template <class T, class U>
  typename std::enable_if<std::is_integral<fixed_type<T, U>>::value, fixed_type<T, U>>::type
  operator () (T l, U r) const {
    return engine() % (r - l) + l;
  }

  template <class T, class U>
  typename std::enable_if<!std::is_integral<fixed_type<T, U>>::value, fixed_type<T, U>>::type
  operator () (T l, U r) const {
    auto res = operator()(static_cast<large_type>(fix_large * l), static_cast<large_type>(fix_large * r));
    return static_cast<fixed_type<T, U>>(res * fix_small);
  }

  void setprecision(int t) {
    fix_large = 1;
    fix_small = 1;
    for (int i = 0; i < t; ++i) {
      fix_large *= 10;
      fix_small *= 0.1L;
    }
  }

};

int main() {
  return 0;
}
