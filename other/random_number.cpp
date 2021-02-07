#pragma once

#include <cstdint>
#include <random>
#include <chrono>
#include <array>
#include <type_traits>

uint64_t engine() {
  static uint64_t result = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());
  result ^= result << 5;
  result ^= result >> 13;
  result ^= result << 7;
  return result;
}

template <class Integer>
typename std::enable_if<std::is_integral<Integer>::value, Integer>::type random_number(Integer lower, Integer upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_int_distribution<Integer>(lower, upper)(gen);
}

template <class Real>
typename std::enable_if<!std::is_integral<Real>::value, Real>::type random_number(Real lower, Real upper) {
  static std::default_random_engine gen(engine());
  return std::uniform_real_distribution<Real>(lower, upper)(gen);
}

/** 
 * @title Random Number
 */