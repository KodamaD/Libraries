
#ifdef DEBUG
#include <iostream>
#include <iomanip>

void dbg_impl() {
  std::cerr << '\n';
}

template <class Head, class... Tail>
void dbg_impl(const Head& head, const Tail&... tail) {
  std::cerr << ' ' << head;
  dbg_impl(tail...);
}

struct dbg_setup {
  dbg_setup() {
    std::cerr << std::boolalpha;
    std::cerr << std::fixed << std::setprecision(5);
  }
} debug_setup;

#define debug(...)\
  do {\
    std::cerr << std::setw(5) << __LINE__ << "  | ";\
    std::cerr << "[" << #__VA_ARGS__ << "]:";\
    dbg_impl(__VA_ARGS__);\
  } while (false)

#define affirm(condition, ...)\
  do {\
    if (!(condition)) {\
      std::cerr << "Affirmation failed: (" << #condition << "), ";\
      if (std::string(#__VA_ARGS__) != "") {\
        std::cerr << "message: " << #__VA_ARGS__ << ", ";\
      }\
      std::cerr << "function " << __func__  << ", ";\
      std::cerr << "file " << __FILE__  << ", ";\
      std::cerr << "line " << __LINE__ << ".\n";\
      std::exit(1);\
    }\
  } while (false)

#else
#define debug(...) ((void) 0)
#define affirm(...) ((void) 0)
#endif
