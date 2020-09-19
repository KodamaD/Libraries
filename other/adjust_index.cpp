#pragma once

#include <cstddef>
#include <cassert>

class adjust_index {
private:
  const size_t M_stuff, M_size;

public:
  explicit adjust_index(const size_t stuff, const size_t size): 
    M_stuff(stuff), M_size(size) 
  { }

  size_t operator [] (const size_t index) const {
    assert(index < M_size);
    return M_stuff + index;
  }
  size_t to_index(const size_t fixed) const {
    assert(fixed >= M_stuff);
    assert(fixed < M_size + M_stuff);
    return fixed - M_stuff;
  }
  size_t size() const {
    return M_size;
  }
};

/**
 * @title Index Adjustment
 */