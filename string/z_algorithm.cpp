
#include <vector>

template <class T>
std::vector<int> z_algorithm(const T& str) {
  int size = str.size();
  std::vector<int> result(size);
  result[0] = size;
  int i = 1, j = 0;
  while (i < size) {
    while (i + j < size && str[i + j] == str[j]) {
      ++j;
    }
    result[i] = j;
    if (j == 0) { 
      ++j; 
      continue; 
    }
    int k = 1;
    while (i + k < size && k + result[k] < j) { 
      result[i + k] = result[k];
      ++k; 
    }
    i += k;
    j -= k;
  }
  return result;
}

int main() {
  return 0;
}
