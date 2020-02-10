
#include <vector>

template <class T>
class matrix: public std::vector<std::vector<typename T::value_type>> {
public:
  using value_type = typename T::value_type;
  using addition = typename T::addition;
  using multiplication = typename T::multiplication;

private:
  const addition add;
  const multiplication mult;

public:
  int height, width;

  matrix(): add(addition()), mult(multiplication()) { }
  matrix(int height_, int width_, const value_type &initial_ = addition().identity):
    add(addition()), mult(multiplication()),
    height(height_), width(width_),
    std::vector<std::vector<value_type>>(height_, std::vector<value_type>(width_, initial_))
  { }
  matrix(const std::vector<std::vector<value_type>> &data_):
    add(addition()), mult(multiplication()),
    height(data_.size()), width(data_.front().size()),
    std::vector<std::vector<value_type>>(data_)
  { }

  matrix operator + (const matrix &rhs) const { return matrix(*this) += rhs; }
  matrix& operator += (const matrix &rhs) { 
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        (*this)[i][j] = add((*this)[i][j], rhs[i][j]);
      }
    }
    return *this;
  }

  matrix& operator *= (const matrix &rhs) { *this = (*this) * rhs; return *this; }
  matrix operator * (const matrix &rhs) const {
    matrix res(height, rhs.width);
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < rhs.width; ++j) {
        for (int k = 0; k < width; ++k) {
          res[i][j] = add(res[i][j], mult((*this)[i][k], rhs[k][j]));
        }
      }
    }
    return res;
  }

  matrix operator * (const value_type &rhs) const { return matrix(*this) *= rhs; }
  matrix& operator *= (const value_type &rhs)  { 
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        (*this)[i][j] = mult((*this)[i][j], rhs);
      }
    }
    return *this;
  }

  matrix power(unsigned long long pow) const {
    matrix res(height, width), use(*this);
    for (int i = 0; i < height; ++i) {
      res[i][i] = mult.identity;
    }
    while (pow > 0) {
      if (pow & 1) {
        res *= use;
      }
      use *= use;
      pow >>= 1;
    }
    return res;
  }

};

int main() {
  return 0;
}