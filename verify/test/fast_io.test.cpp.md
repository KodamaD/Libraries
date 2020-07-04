---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :x: test/fast_io.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/fast_io.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-04 16:35:04+09:00


* see: <a href="https://judge.yosupo.jp/problem/many_aplusb">https://judge.yosupo.jp/problem/many_aplusb</a>


## Depends on

* :question: <a href="../../library/other/fast_io.cpp.html">other/fast_io.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../other/fast_io.cpp"

int main() {
  size_t Q;
  cin.scan(Q);
  while (Q--) {
    uint64_t a, b;
    cin.scan(a, b);
    cout.println(a + b);
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/fast_io.test.cpp"

#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#line 2 "other/fast_io.cpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

namespace fast_io {
  static constexpr size_t buf_size = 1 << 18;
  static constexpr size_t buf_margin = 1;
  static constexpr size_t block_size = 10000;
  static constexpr size_t integer_size = 20;

  static char inbuf[buf_size + buf_margin] = {};
  static char outbuf[buf_size + buf_margin] = {};
  static char block_str[block_size * 4 + buf_margin] = {};

  static constexpr uint64_t power10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
    1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000,
    100000000000000, 1000000000000000, 10000000000000000, 100000000000000000,
    1000000000000000000, 10000000000000000000u
  };

  class scanner {
  private:
    size_t M_in_pos = 0, M_in_end = buf_size;

    void M_load() { 
      M_in_end = fread(inbuf, 1, buf_size, stdin); 
      inbuf[M_in_end] = '\0';  
    }
    void M_reload() {
      size_t length = M_in_end - M_in_pos;
      memmove(inbuf, inbuf + M_in_pos, length);
      M_in_end = length + fread(inbuf + length, 1, buf_size - length, stdin);
      inbuf[M_in_end] = '\0';
      M_in_pos = 0;
    }

    void M_ignore_space() {
      while (inbuf[M_in_pos] <= ' ') {
        if (__builtin_expect(++M_in_pos == M_in_end, 0)) M_reload();
      }
    }

    char M_next() { return inbuf[M_in_pos++]; }
    char M_next_nonspace() {
      M_ignore_space();
      return inbuf[M_in_pos++];
    }

  public:
    scanner() { M_load(); }
    
    void scan(char &c) { c = M_next_nonspace(); }
    void scan(std::string &s) {
      M_ignore_space();
      s = "";
      do {
        size_t start = M_in_pos;
        while (inbuf[M_in_pos] > ' ') ++M_in_pos;
        s += std::string(inbuf + start, inbuf + M_in_pos);
        if (inbuf[M_in_pos] != '\0') break;
        M_reload();
      } while (true);
    }

    template <class T>
    typename std::enable_if<std::is_integral<T>::value, void>::type scan(T &x) {
      char c = M_next_nonspace();
      if (__builtin_expect(M_in_pos + integer_size >= M_in_end, 0)) M_reload();
      bool n = false;
      if (c == '-') n = true, x = 0;
      else x = c & 15;
      while ((c = M_next()) >= '0') x = x * 10 + (c & 15);
      if (n) x = -x;
    }

    template <class T, class... Args>
    void scan(T &x, Args&... args) {
      scan(x); scan(args...);
    }

    template <class T>
    scanner& operator >> (T &x) {
      scan(x); return *this;
    }

  };

  class printer {
  private:
    size_t M_out_pos = 0;

    void M_flush() {
      fwrite(outbuf, 1, M_out_pos, stdout);
      M_out_pos = 0;
    }

    void M_precompute() {
      for (size_t i = 0; i < block_size; ++i) {
        size_t j = 4, k = i;
        while (j--) {
          block_str[i * 4 + j] = k % 10 + '0';
          k /= 10;
        }
      }
    }

    static constexpr size_t S_integer_digits(uint64_t n) {
      if (n >= power10[10]) {
        if (n >= power10[19]) return 20;
        if (n >= power10[18]) return 19;
        if (n >= power10[17]) return 18;
        if (n >= power10[16]) return 17;
        if (n >= power10[15]) return 16;
        if (n >= power10[14]) return 15;
        if (n >= power10[13]) return 14;
        if (n >= power10[12]) return 13;
        if (n >= power10[11]) return 12;
        return 11;
      }
      else {
        if (n >= power10[9]) return 10;
        if (n >= power10[8]) return 9;
        if (n >= power10[7]) return 8;
        if (n >= power10[6]) return 7;
        if (n >= power10[5]) return 6;
        if (n >= power10[4]) return 5;
        if (n >= power10[3]) return 4;
        if (n >= power10[2]) return 3;
        if (n >= power10[1]) return 2;
        return 1;
      }
    }

  public:
    printer() { M_precompute(); }
    ~printer() { M_flush(); }

    void print(char c) { 
      outbuf[M_out_pos++] = c;
      if (__builtin_expect(M_out_pos == buf_size, 0)) M_flush();
    }
    void print(const char *s) {
      while (*s != 0) {
        outbuf[M_out_pos++] = *s++;
        if (M_out_pos == buf_size) M_flush();
      }
    }
    void print(const std::string &s) {
      for (auto c: s) {
        outbuf[M_out_pos++] = c;
        if (M_out_pos == buf_size) M_flush();
      }
    }
    
    template <class T>
    typename std::enable_if<std::is_integral<T>::value, void>::type print(T x) {
      if (__builtin_expect(M_out_pos + integer_size >= buf_size, 0)) M_flush();
      if (x < 0) print('-'), x = -x;
      size_t digit = S_integer_digits(x);
      size_t len = digit;
      while (len >= 4) {
        len -= 4;
        memcpy(outbuf + M_out_pos + len, block_str + (x % block_size) * 4, 4);
        x /= 10000;
      }
      memcpy(outbuf + M_out_pos, block_str + x * 4 + 4 - len, len);
      M_out_pos += digit;
    }

    template <class T, class... Args>
    void print(const T &x, const Args&... args) {
      print(x); print(' '); print(args...);
    }

    template <class... Args>
    void println(const Args&... args) {
      print(args...); print('\n');
    }

    template <class T>
    printer& operator << (const T &x) {
      print(x); return *this;
    }

  };

};
#line 5 "test/fast_io.test.cpp"

int main() {
  size_t Q;
  cin.scan(Q);
  while (Q--) {
    uint64_t a, b;
    cin.scan(a, b);
    cout.println(a + b);
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

