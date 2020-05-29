
template <class T>
class randomized_queue {
public:
  using value_type = T;

  static uint64_t engine() {
    static uint64_t current = 7511168;
    current ^= (current << 9);
    current ^= (current >> 7);
    return current;
  }
  
private:
  std::vector<value_type> data;

public:
  randomized_queue() = default;
  randomized_queue(const std::vector<value_type> &data_): data(data_) { shuffle(); }

  void shuffle() {
    std::swap(data.back(), data[engine() % data.size()]);
  }

  value_type front() const {
    return data.back();
  }
  bool empty() const {
    return data.empty();
  }
  size_t size() const {
    return data.size();
  }

  void push(const value_type &val) {
    data.push_back(val);
    shuffle();
  }
  void pop() {
    data.pop_back();
    if (!data.empty()) {
      shuffle();
    }
  }

};
