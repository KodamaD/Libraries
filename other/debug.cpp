#pragma once

#ifdef LOCAL
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>

struct debug_support {

  std::ofstream file;
  std::stringstream to_str_helper;
  clock_t start_time;
  size_t str_width;

  debug_support() {
    file.open("debug.txt");
    if (!file.is_open()) {
      std::cerr << "\033[31m failed to open the file 'debug.txt' \033[0m \n";
      std::exit(EXIT_FAILURE);
    }
    file << "\n<debug output file>\n\n";
    to_str_helper << std::boolalpha;
    to_str_helper << std::fixed;
    setwidth(3);
    setprecision(6);
    settime();
  }
  ~debug_support() {
    std::system("code -r debug.txt");
    file.close(); 
  }

  void setwidth(size_t x) {
    str_width = x;
  }
  void setprecision(size_t x) {
    to_str_helper << std::setprecision(x);
  }
  void settime() {
    start_time = std::clock();
  }

  std::string to_str(char c) { 
    return std::string("'") + c + "'"; 
  }
  std::string to_str(const std::string &s) { 
    return std::string("\"") + s + "\""; 
  }
  std::string to_str(const char *s) { 
    return std::string("\"") + s + "\""; 
  }

  template <class T, class U>
  std::string to_str(const std::pair<T, U> &x) { 
    return "(" + to_str(x.first) + ", " + to_str(x.second) + ")"; 
  }
  template <class T, size_t I>
  typename std::enable_if<(I + 1 == std::tuple_size<T>::value), std::string>::type to_str_tuple(const T &x) { 
    return to_str(std::get<I>(x)); 
  } 
  template <class T, size_t I>
  typename std::enable_if<(I + 1 != std::tuple_size<T>::value), std::string>::type to_str_tuple(const T &x) { 
    return to_str(std::get<I>(x)) + ", " + to_str_tuple<T, I + 1>(x);
  } 
  template <class... Args>
  std::string to_str(const std::tuple<Args...> &x) {
    return "(" + to_str_tuple<std::tuple<Args...>, 0>(x) + ")";
  }

  template <class T>
  std::string to_str(const T &x) {
    to_str_helper << x;
    std::string s;
    std::getline(to_str_helper, s);
    to_str_helper.str("");
    to_str_helper.clear(std::stringstream::goodbit);
    return s;
  }
  template <class T, class U, class... Args>
  std::string to_str(const T &x, const U &y, const Args&... args) { 
    return x == y ? "__" : to_str(x, args...); 
  }

  std::string fix_str(const std::string &s) {
    if (s.size() >= str_width) return s;
    return std::string(str_width - s.size(), ' ') + s;
  }

  template <class T, class U = void>
  struct has_iterator: public std::false_type {};
  template <class T>
  struct has_iterator<T, typename std::conditional<false, typename T::iterator, void>::type>: public std::true_type {};

  template <class T, class... Args>
  typename std::enable_if<has_iterator<typename T::value_type>::value, std::string>::type 
  to_str_container(const T &x, const Args&... args) {
    std::string s;
    for (const auto &v: x) {
      s += to_str_container(v, args...);
    }
    return s + '\n';
  }
  template <class T, class... Args>
  typename std::enable_if<!has_iterator<typename T::value_type>::value, std::string>::type 
  to_str_container(const T &x, const Args&... args) {
    std::string s = "{ ";
    bool f = false;
    for (const auto &v: x) {
      if (f) s += ", ";
      f = true;
      s += fix_str(to_str(v, args...));
    }
    return s + " }\n";
  }

  template <class T>
  void print(const T &x) { 
    file << to_str(x) << std::endl;
  }
  template <class T, class... Args>
  void print(const T &x, const Args&... args) {
    file << to_str(x) << ", ";
    print(args...);
  }

  template <class T, class... Args>
  void print_container(const T &x, const Args&... args) {
    file << to_str_container(x, args...) << std::endl;
    setwidth(3);
  }

} debugger;

#define show(...)\
  do {\
    debugger.file << "<line:" << std::setw(4) << __LINE__ << ">";\
    debugger.file << " [" << #__VA_ARGS__ << "]: ";\
    debugger.print(__VA_ARGS__);\
  } while (false)

#define show_c(x, ...)\
 do {\
    debugger.file << "\n<line:" << std::setw(4) << __LINE__ << ">";\
    debugger.file << " [" << #x << "]";\
    if (std::string(#__VA_ARGS__).empty()) debugger.file << ":\n";\
    else debugger.file << " (ignore " << #__VA_ARGS__ << "):\n";\
    debugger.print_container(x __VA_OPT__(,) __VA_ARGS__);\
 } while (false)

#define show_e()\
  do {\
    double d = static_cast<double>(std::clock() - debugger.start_time);\
    debugger.file << "<line:" << std::setw(4) << __LINE__ << ">";\
    debugger.file << " elapsed time: " << d * 1000 / CLOCKS_PER_SEC << "ms" << std::endl;\
  } while (false)

#else
#define show(...) ((void) 0)
#define show_c(...) ((void) 0)
#define show_e() ((void) 0)
#endif

/**
 * @title Debugger
 */