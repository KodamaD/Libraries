#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>

class measure {
public:
  using time_point = decltype(std::chrono::system_clock::now());

private:
  const time_point M_start;

  static time_point S_current_time() {
    return std::chrono::system_clock::now();
  }

public:
  explicit measure(): M_start(S_current_time()) { }

  template <class Duration = std::chrono::milliseconds>
  uint64_t get() const {
    return std::chrono::duration_cast<Duration>(S_current_time() - M_start).count();
  }

  void print_ms() const {
    std::cerr << "current time: " << get<std::chrono::milliseconds>() << "ms" << std::endl;
  }

};

/**
 * @title Time Measurement
 */