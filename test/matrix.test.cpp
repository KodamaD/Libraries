
#define PROBLEM "https://yukicoder.me/problems/no/1105"

#include "../algebraic/modular.cpp"
#include "../container/matrix.cpp"

#include <iostream>
#include <cstdint>

using m32 = mint32_t<1000000007>;

struct semiring {
  struct value_structure {
    using type = m32;
    static type addition_identity() { return m32(0); }
    static type addition(const type& v1, const type& v2) { 
      return v1 + v2;
    }
    static type multiplication_identity() { return m32(1); }
    static type multiplication(const type& v1, const type& v2) { 
      return v1 * v2;
    }
  };
};

int main() {
  int64_t N;
  std::cin >> N;
  int32_t a, b, c;
  std::cin >> a >> b >> c;
  using matrix_t = matrix<semiring>;
  matrix_t mult({ 
    { m32(1), m32(0), m32(-1) },
    { m32(-1), m32(1), m32(0) },
    { m32(0), m32(-1), m32(1) },
  });
  matrix_t start({
    { m32(a), m32(b), m32(c) }
  });
  start *= mult.power(N - 1);
  std::cout << start[0][0] << ' ' << start[0][1] << ' ' << start[0][2] << '\n';
  return 0;
}
