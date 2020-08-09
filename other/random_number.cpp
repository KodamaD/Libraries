#pragma once

#include <cstdint>
#include <random>
#include <chrono>
#include <array>
#include <type_traits>

uint64_t engine() {
  static const auto rotate = [](const uint64_t x, const size_t k) {
    return (x << k) | (x >> (64 - k));
  };
  static auto array = [] {
    uint64_t seed = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());
    std::array<uint64_t, 4> res{};
    for (size_t index = 0; index < 4; index++) {
      uint64_t value = (seed += 0x9e3779b97f4a7c15);
      value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9;
      value = (value ^ (value >> 27)) * 0x94d049bb133111eb;
      res[index] = value ^ (value >> 31);
    }
    return res;
  }();
  const uint64_t result = rotate(array[1] * 5, 7) * 9;
  const uint64_t old_value = array[1] << 17;
  array[2] ^= array[0];
  array[3] ^= array[1];
  array[1] ^= array[2];
  array[0] ^= array[3];
  array[2] ^= old_value;
  array[3] = rotate(array[3], 45);
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