---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/fast_io.cpp
    title: Fast Input/Output
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/fast_io.test.cpp\"\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\
    \n\n#line 2 \"other/fast_io.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <cstring>\n#include <iostream>\n\nnamespace fast_io {\n  static constexpr\
    \ size_t buf_size = 1 << 18;\n  static constexpr size_t buf_margin = 1;\n  static\
    \ constexpr size_t block_size = 10000;\n  static constexpr size_t integer_size\
    \ = 20;\n\n  static char inbuf[buf_size + buf_margin] = {};\n  static char outbuf[buf_size\
    \ + buf_margin] = {};\n  static char block_str[block_size * 4 + buf_margin] =\
    \ {};\n\n  static constexpr uint64_t power10[] = {\n    1, 10, 100, 1000, 10000,\
    \ 100000, 1000000, 10000000, 100000000,\n    1000000000, 10000000000, 100000000000,\
    \ 1000000000000, 10000000000000,\n    100000000000000, 1000000000000000, 10000000000000000,\
    \ 100000000000000000,\n    1000000000000000000, 10000000000000000000u\n  };\n\n\
    \  class scanner {\n  private:\n    size_t M_in_pos = 0, M_in_end = buf_size;\n\
    \n    void M_load() { \n      M_in_end = fread(inbuf, 1, buf_size, stdin); \n\
    \      inbuf[M_in_end] = '\\0';  \n    }\n    void M_reload() {\n      size_t\
    \ length = M_in_end - M_in_pos;\n      memmove(inbuf, inbuf + M_in_pos, length);\n\
    \      M_in_end = length + fread(inbuf + length, 1, buf_size - length, stdin);\n\
    \      inbuf[M_in_end] = '\\0';\n      M_in_pos = 0;\n    }\n\n    void M_ignore_space()\
    \ {\n      while (inbuf[M_in_pos] <= ' ') {\n        if (__builtin_expect(++M_in_pos\
    \ == M_in_end, 0)) M_reload();\n      }\n    }\n\n    char M_next() { return inbuf[M_in_pos++];\
    \ }\n    char M_next_nonspace() {\n      M_ignore_space();\n      return inbuf[M_in_pos++];\n\
    \    }\n\n  public:\n    scanner() { M_load(); }\n    \n    void scan(char &c)\
    \ { c = M_next_nonspace(); }\n    void scan(std::string &s) {\n      M_ignore_space();\n\
    \      s = \"\";\n      do {\n        size_t start = M_in_pos;\n        while\
    \ (inbuf[M_in_pos] > ' ') ++M_in_pos;\n        s += std::string(inbuf + start,\
    \ inbuf + M_in_pos);\n        if (inbuf[M_in_pos] != '\\0') break;\n        M_reload();\n\
    \      } while (true);\n    }\n\n    template <class T>\n    typename std::enable_if<std::is_integral<T>::value,\
    \ void>::type scan(T &x) {\n      char c = M_next_nonspace();\n      if (__builtin_expect(M_in_pos\
    \ + integer_size >= M_in_end, 0)) M_reload();\n      bool n = false;\n      if\
    \ (c == '-') n = true, x = 0;\n      else x = c & 15;\n      while ((c = M_next())\
    \ >= '0') x = x * 10 + (c & 15);\n      if (n) x = -x;\n    }\n\n    template\
    \ <class T, class... Args>\n    void scan(T &x, Args&... args) {\n      scan(x);\
    \ scan(args...);\n    }\n\n    template <class T>\n    scanner& operator >> (T\
    \ &x) {\n      scan(x); return *this;\n    }\n\n  };\n\n  class printer {\n  private:\n\
    \    size_t M_out_pos = 0;\n\n    void M_flush() {\n      fwrite(outbuf, 1, M_out_pos,\
    \ stdout);\n      M_out_pos = 0;\n    }\n\n    void M_precompute() {\n      for\
    \ (size_t i = 0; i < block_size; ++i) {\n        size_t j = 4, k = i;\n      \
    \  while (j--) {\n          block_str[i * 4 + j] = k % 10 + '0';\n          k\
    \ /= 10;\n        }\n      }\n    }\n\n    static constexpr size_t S_integer_digits(uint64_t\
    \ n) {\n      if (n >= power10[10]) {\n        if (n >= power10[19]) return 20;\n\
    \        if (n >= power10[18]) return 19;\n        if (n >= power10[17]) return\
    \ 18;\n        if (n >= power10[16]) return 17;\n        if (n >= power10[15])\
    \ return 16;\n        if (n >= power10[14]) return 15;\n        if (n >= power10[13])\
    \ return 14;\n        if (n >= power10[12]) return 13;\n        if (n >= power10[11])\
    \ return 12;\n        return 11;\n      }\n      else {\n        if (n >= power10[9])\
    \ return 10;\n        if (n >= power10[8]) return 9;\n        if (n >= power10[7])\
    \ return 8;\n        if (n >= power10[6]) return 7;\n        if (n >= power10[5])\
    \ return 6;\n        if (n >= power10[4]) return 5;\n        if (n >= power10[3])\
    \ return 4;\n        if (n >= power10[2]) return 3;\n        if (n >= power10[1])\
    \ return 2;\n        return 1;\n      }\n    }\n\n  public:\n    printer() { M_precompute();\
    \ }\n    ~printer() { M_flush(); }\n\n    void print(char c) { \n      outbuf[M_out_pos++]\
    \ = c;\n      if (__builtin_expect(M_out_pos == buf_size, 0)) M_flush();\n   \
    \ }\n    void print(const char *s) {\n      while (*s != 0) {\n        outbuf[M_out_pos++]\
    \ = *s++;\n        if (M_out_pos == buf_size) M_flush();\n      }\n    }\n   \
    \ void print(const std::string &s) {\n      for (auto c: s) {\n        outbuf[M_out_pos++]\
    \ = c;\n        if (M_out_pos == buf_size) M_flush();\n      }\n    }\n    \n\
    \    template <class T>\n    typename std::enable_if<std::is_integral<T>::value,\
    \ void>::type print(T x) {\n      if (__builtin_expect(M_out_pos + integer_size\
    \ >= buf_size, 0)) M_flush();\n      if (x < 0) print('-'), x = -x;\n      size_t\
    \ digit = S_integer_digits(x);\n      size_t len = digit;\n      while (len >=\
    \ 4) {\n        len -= 4;\n        memcpy(outbuf + M_out_pos + len, block_str\
    \ + (x % block_size) * 4, 4);\n        x /= 10000;\n      }\n      memcpy(outbuf\
    \ + M_out_pos, block_str + x * 4 + 4 - len, len);\n      M_out_pos += digit;\n\
    \    }\n\n    template <class T, class... Args>\n    void print(const T &x, const\
    \ Args&... args) {\n      print(x); print(' '); print(args...);\n    }\n\n   \
    \ template <class... Args>\n    void println(const Args&... args) {\n      print(args...);\
    \ print('\\n');\n    }\n\n    template <class T>\n    printer& operator << (const\
    \ T &x) {\n      print(x); return *this;\n    }\n\n  };\n\n};\n\n/**\n * @title\
    \ Fast Input/Output\n */\n#line 5 \"test/fast_io.test.cpp\"\n\n#line 8 \"test/fast_io.test.cpp\"\
    \n\nfast_io::scanner cin;\nfast_io::printer cout;\n\nint main() {\n  size_t Q;\n\
    \  cin.scan(Q);\n  while (Q--) {\n    uint64_t a, b;\n    cin.scan(a, b);\n  \
    \  cout.println(a + b);\n  }\n}\n"
  code: "\n#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ \"../other/fast_io.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\nfast_io::scanner\
    \ cin;\nfast_io::printer cout;\n\nint main() {\n  size_t Q;\n  cin.scan(Q);\n\
    \  while (Q--) {\n    uint64_t a, b;\n    cin.scan(a, b);\n    cout.println(a\
    \ + b);\n  }\n}\n"
  dependsOn:
  - other/fast_io.cpp
  isVerificationFile: true
  path: test/fast_io.test.cpp
  requiredBy: []
  timestamp: '2020-07-11 19:42:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fast_io.test.cpp
layout: document
redirect_from:
- /verify/test/fast_io.test.cpp
- /verify/test/fast_io.test.cpp.html
title: test/fast_io.test.cpp
---
