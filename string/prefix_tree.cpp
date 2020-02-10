
#include <vector>
#include <algorithm>
#include <string>

template <int LETTER = 26>
class prefix_tree {
private:
  struct node {
    int index;
    int next[LETTER];
    char letter;
    node(char c): letter(c), index(-1) {
      std::fill(next, next + LETTER, -1);
    }
  };

  const char base;
  std::vector<node> data;

  int& next(int i, int j) {
    return data[i].next[j];
  }

public:
  prefix_tree(char base = 'a', char root = '$'): base(base) { data.emplace_back(root); }

  void add(const std::string& str, int index) {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (next(pos, k) != -1) {
        pos = next(pos, k);
        continue;
      }
      int pos_new = data.size();
      next(pos, k) = pos_new;
      data.emplace_back(str[i]);
      pos = pos_new;
    }
    data[pos].index = index;
  }

  int find(const std::string& str) const {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (next(pos, k) == -1) return -1;
      pos = next(pos, k);
    }
    return pos;
  }

  int find(int i, char c) const {
    return next(i, c - base);
  }

  int index(int i) const {
    return i == -1 ? -1 : data[i].index;
  }

};

int main() {
  return 0;
}