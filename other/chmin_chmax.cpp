#pragma once

template <class T, class U>
constexpr bool chmin(T &lhs, const U &rhs) {
  if (lhs > rhs) { 
    lhs = rhs; 
    return true; 
  }
  return false;
}

template <class T, class U>
constexpr bool chmax(T &lhs, const U &rhs) {
  if (lhs < rhs) { 
    lhs = rhs; 
    return true; 
  }
  return false;
}

/**
 * @title Chmin/Chmax
 */