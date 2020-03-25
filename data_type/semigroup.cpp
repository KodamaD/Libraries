
template <class T>
struct range_max {
  using value_type = T;
  struct value_operation {
    value_type operator () (const value_type &x, const value_type &y) const {
      return x > y ? x : y;
    }
  };
};

template <class T>
struct range_min {
  using value_type = T;
  struct value_operation {
    value_type operator () (const value_type &x, const value_type &y) const {
      return x < y ? x : y;
    }
  };
};

template <class T>
struct range_sum {
  using value_type = T;
  struct value_operation {
    value_type operator () (const value_type &x, const value_type &y) const {
      return x + y;
    }
  };
};


template <class T>
struct range_product {
  using value_type = T;
  struct value_operation {
    value_type operator () (const value_type &x, const value_type &y) const {
      return x * y;
    }
  };
};

int main() {
  return 0;
}