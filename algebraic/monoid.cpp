
#include <limits>
template <class T>
struct range_min_single_assign {
  using value_type = T;
  using effector_type = T;
  struct value_operation {
    value_type identity = std::numeric_limits<T>::max();
    value_type operator () (const value_type &x, const value_type &y) const {
      return x < y ? x : y;
    }
  };
  struct merge_operation {
    value_type operator () (const value_type &x, const effector_type &y) const {
      return y;
    }
  };
};

#include <limits>
template <class T>
struct range_max_single_assign {
  using value_type = T;
  using effector_type = T;
  struct value_operation {
    value_type identity = std::numeric_limits<T>::min();
    value_type operator () (const value_type &x, const value_type &y) const {
      return x > y ? x : y;
    }
  };
  struct merge_operation {
    value_type operator () (const value_type &x, const effector_type &y) const {
      return y;
    }
  };
};

#include <limits>
template <class T>
struct range_min_single_chmin {
  using value_type = T;
  using effector_type = T;
  struct value_operation {
    value_type identity = std::numeric_limits<T>::max();
    value_type operator () (const value_type &x, const value_type &y) const {
      return x < y ? x : y;
    }
  };
  struct merge_operation {
    value_type operator () (const value_type &x, const effector_type &y) const {
      return x < y ? x : y;
    }
  };
};

#include <limits>
template <class T>
struct range_max_single_chmax {
  using value_type = T;
  using effector_type = T;
  struct value_operation {
    value_type identity = std::numeric_limits<T>::min();
    value_type operator () (const value_type &x, const value_type &y) const {
      return x > y ? x : y;
    }
  };
  struct merge_operation {
    value_type operator () (const value_type &x, const effector_type &y) const {
      return x > y ? x : y;
    }
  };
};

template <class T>
struct range_sum_single_assign {
  using value_type = T;
  using effector_type = T;
  struct value_operation {
    value_type identity = 0;
    value_type operator () (const value_type &x, const value_type &y) const {
      return x + y;
    }
  };
  struct merge_operation {
    value_type operator () (const value_type &x, const effector_type &y) const {
      return y;
    }
  };
};

template <class T>
struct range_sum_single_add {
  using value_type = T;
  using effector_type = T;
  struct value_operation {
    value_type identity = 0;
    value_type operator () (const value_type &x, const value_type &y) const {
      return x + y;
    }
  };
  struct merge_operation {
    value_type operator () (const value_type &x, const effector_type &y) const {
      return x + y;
    }
  };
};

int main() {
  return 0;
}