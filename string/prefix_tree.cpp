
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

public:
  prefix_tree(char base = 'a', char root = '$'): base(base) { data.emplace_back(root); }

  void add(const std::string& str, int index) {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (data[pos].next[k] != -1) {
        pos = data[pos].next[k];
        continue;
      }
      int pos_new = data.size();
      data[pos].next[k] = pos_new;
      data.emplace_back(str[i]);
      pos = pos_new;
    }
    data[pos].index = index;
  }

  int find(const std::string& str) const {
    int pos = 0;
    for (int i = 0; i < str.size(); ++i) {
      int k = str[i] - base;
      if (data[pos].next[k] == -1) {
        return -1;
      }
      pos = data[pos].next[k];
    }
    return pos;
  }

  int find(int i, char c) const {
    return data[i].next[c - base];
  }

  int index(int i) const {
    return i == -1 ? -1 : data[i].index;
  }

};

int main() {
  return 0;
}