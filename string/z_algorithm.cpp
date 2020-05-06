
template <class T>
std::vector<size_t> z_algorithm(const T& str) {
  size_t size = str.size();
  std::vector<size_t> result(size);
  result[0] = size;
  size_t i = 1, j = 0;
  while (i < size) {
    while (i + j < size && str[i + j] == str[j]) {
      ++j;
    }
    result[i] = j;
    if (j == 0) { 
      ++i; 
      continue; 
    }
    size_t k = 1;
    while (i + k < size && k + result[k] < j) { 
      result[i + k] = result[k];
      ++k; 
    }
    i += k;
    j -= k;
  }
  return result;
}
