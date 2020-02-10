
#include <stack>

template <class T>
class sliding_window_aggregation {
public:
  using value_type = typename T::value_type;
  using value_operation = typename T::value_operation;

private:
  struct node {
    value_type value, sum;
    node (const value_type &value_, const value_type &sum): value(value_), sum(sum_) { }
  };
  const value_operation op;
  std::stack<node> front, back;

public:
  sliding_window_aggregation(): op(value_operation()), front(), back() { }

  value_type fold() const {
    if (front.empty()) {
      return back.top().sum;
    } 
    else if (back.empty()) {
      return front.top().sum;
    } 
    else {
      return op(front.top().sum, back.top().sum);
    }
  }

  void push(const value_type &x) {
    if (back.empty()) {
      back.emplace(x, x);
    } 
    else {
      value_type tmp = op(back.top().sum, x);
      back.emplace(x, tmp);
    }
  }

  void pop() {
    if (front.empty()) {
      front.emplace(back.top().value, back.top().value);
      back.pop();
      while (!back.empty()) {
        value_type tmp = op(back.top().value, front.top().sum);
        front.emplace(back.top().value, tmp);
        back.pop();
      }
    }
    front.pop();
  }

};

int main() {
  return 0;
}