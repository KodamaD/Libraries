
template <class T>
struct number {
  using value_type = T;
  struct addition {
    value_type identity = 0;
    value_type operator () (const value_type &x, const value_type &y) const {
      return x + y;
    }
  };
  struct multiplication {
    value_type identity = 1;
    value_type operator () (const value_type &x, const value_type &y) const {
      return x * y;
    }
  };
};

#include <limits>
template <class T>
struct xor_and {
  using value_type = T;
  struct addition {
    value_type identity = 0;
    value_type operator () (const value_type &x, const value_type &y) const {
      return x ^ y;
    }
  };
  struct multiplication {
    value_type identity = std::numeric_limits<T>::max();
    value_type operator () (const value_type &x, const value_type &y) const {
      return x & y;
    }
  };
};

#include <limits>
template <class T>
struct min_add {
  using value_type = T;
  struct addition {
    value_type identity = std::numeric_limits<T>::max();
    value_type operator () (const value_type &x, const value_type &y) const {
      return x < y ? x : y;
    }
  };
  struct multiplication {
    value_type identity = 0;
    value_type operator () (const value_type &x, const value_type &y) const {
      return x + y;
    }
  };
};

#include <limits>
template <class T>
struct max_add {
  using value_type = T;
  struct addition {
    value_type identity = std::numeric_limits<T>::min();
    value_type operator () (const value_type &x, const value_type &y) const {
      return x > y ? x : y;
    }
  };
  struct multiplication {
    value_type identity = 0;
    value_type operator () (const value_type &x, const value_type &y) const {
      return x + y;
    }
  };
};

int main() {
  return 0;
}