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


# :warning: container/randomized_queue.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5f0b6ebc4bea10285ba2b8a6ce78b863">container</a>
* <a href="{{ site.github.repository_url }}/blob/master/container/randomized_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-29 10:25:13+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class T>
class randomized_queue {
public:
  using value_type = T;

  static uint64_t engine() {
    static uint64_t current = 7511168;
    current ^= (current << 9);
    current ^= (current >> 7);
    return current;
  }
  
private:
  std::vector<value_type> data;

public:
  randomized_queue() = default;
  randomized_queue(const std::vector<value_type> &data_): data(data_) { shuffle(); }

  void shuffle() {
    std::swap(data.back(), data[engine() % data.size()]);
  }

  value_type front() const {
    return data.back();
  }
  bool empty() const {
    return data.empty();
  }
  size_t size() const {
    return data.size();
  }

  void push(const value_type &val) {
    data.push_back(val);
    shuffle();
  }
  void pop() {
    data.pop_back();
    if (!data.empty()) {
      shuffle();
    }
  }

};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "container/randomized_queue.cpp"

template <class T>
class randomized_queue {
public:
  using value_type = T;

  static uint64_t engine() {
    static uint64_t current = 7511168;
    current ^= (current << 9);
    current ^= (current >> 7);
    return current;
  }
  
private:
  std::vector<value_type> data;

public:
  randomized_queue() = default;
  randomized_queue(const std::vector<value_type> &data_): data(data_) { shuffle(); }

  void shuffle() {
    std::swap(data.back(), data[engine() % data.size()]);
  }

  value_type front() const {
    return data.back();
  }
  bool empty() const {
    return data.empty();
  }
  size_t size() const {
    return data.size();
  }

  void push(const value_type &val) {
    data.push_back(val);
    shuffle();
  }
  void pop() {
    data.pop_back();
    if (!data.empty()) {
      shuffle();
    }
  }

};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

