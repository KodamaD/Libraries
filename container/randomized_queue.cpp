
#include <vector>
#include <algorithm>
#include <ctime>

template <class T>
class randomized_queue {
public:
  using value_type = T;

private:
  std::vector<value_type> data;

  inline unsigned engine() const {
    static unsigned current = std::clock() ^ std::time(nullptr);
    current ^= current << 13;
    current ^= current >> 17;
    current ^= current << 5;
    return current;
  }

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
  unsigned size() const {
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

int main() {
  return 0;
}
