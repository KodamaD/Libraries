
namespace fast_io {
  static constexpr size_t buf_size = 1 << 18;
  static constexpr size_t buf_margin = 1;
  static constexpr size_t block_size = 10000;
  static constexpr size_t integer_size = 20;
  size_t in_pos = 0, in_end = buf_size, out_pos = 0;

  static char inbuf[buf_size + buf_margin] = {};
  static char outbuf[buf_size + buf_margin] = {};
  static char block_str[block_size * 4 + buf_margin] = {};

  template <class T, class U>
  using if_integral = typename std::enable_if<std::is_integral<T>::value, U>::type;

  static constexpr uint_fast64_t power10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
    1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000,
    100000000000000, 1000000000000000, 10000000000000000, 100000000000000000,
    1000000000000000000, 10000000000000000000u
  };

  class scanner {
  private:
    void M_load() { 
      in_end = fread(inbuf, 1, buf_size, stdin); 
      inbuf[in_end] = '\0';  
    }
    void M_reload() {
      size_t length = in_end - in_pos;
      memmove(inbuf, inbuf + in_pos, length);
      in_end = length + fread(inbuf + length, 1, buf_size - length, stdin);
      inbuf[in_end] = '\0';
      in_pos = 0;
    }

    void M_ignore_space() {
      while (inbuf[in_pos] <= ' ') {
        if (__builtin_expect(++in_pos == in_end, 0)) M_reload();
      }
    }

    char M_next() { return inbuf[in_pos++]; }
    char M_next_nonspace() {
      M_ignore_space();
      return inbuf[in_pos++];
    }

  public:
    scanner() { M_load(); }
    
    void scan(char &c) { c = M_next_nonspace(); }
    void scan(std::string &s) {
      M_ignore_space();
      s = "";
      do {
        size_t start = in_pos;
        while (inbuf[in_pos] > ' ') ++in_pos;
        s += std::string(inbuf + start, inbuf + in_pos);
        if (inbuf[in_pos] != '\0') break;
        M_reload();
      } while (true);
    }

    template <class T>
    if_integral<T, void> scan(T &x) {
      char c = M_next_nonspace();
      if (__builtin_expect(in_pos + integer_size >= in_end, 0)) M_reload();
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

  };

  class printer {
  private:
    void M_flush() {
      fwrite(outbuf, 1, out_pos, stdout);
      out_pos = 0;
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

    static constexpr size_t M_integer_digits(uint_fast64_t n) {
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
      outbuf[out_pos++] = c;
      if (__builtin_expect(out_pos == buf_size, 0)) M_flush();
    }
    void print(const char *s) {
      while (*s != 0) {
        outbuf[out_pos++] = *s++;
        if (out_pos == buf_size) M_flush();
      }
    }
    void print(const std::string &s) {
      for (auto c: s) {
        outbuf[out_pos++] = c;
        if (out_pos == buf_size) M_flush();
      }
    }
    
    template <class T>
    if_integral<T, void> print(T x) {
      if (__builtin_expect(out_pos + integer_size >= buf_size, 0)) M_flush();
      if (x < 0) print('-'), x = -x;
      size_t digit = M_integer_digits(x);
      size_t len = digit;
      while (len >= 4) {
        len -= 4;
        memcpy(outbuf + out_pos + len, block_str + (x % block_size) * 4, 4);
        x /= 10000;
      }
      memcpy(outbuf + out_pos, block_str + x * 4 + 4 - len, len);
      out_pos += digit;
    }

    template <class T, class... Args>
    void print(const T &x, const Args&... args) {
      print(x); print(' '); print(args...);
    }

    template <class... Args>
    void println(const Args&... args) {
      print(args...); print('\n');
    }

  };

};

fast_io::scanner cin;
fast_io::printer cout;
