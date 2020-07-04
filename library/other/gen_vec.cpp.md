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


# :warning: other/gen_vec.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/gen_vec.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-03 23:58:07+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

template <class T, size_t N, size_t I = 0>
decltype(auto) gen_vec(const size_t (&)[N], typename std::enable_if<(I == N), const T&>::type value = T{}) { 
  return value; 
}

template <class T, size_t N, size_t I = 0>
decltype(auto) gen_vec(const size_t (&list)[N], typename std::enable_if<(I != N), const T&>::type value = T{}) { 
  return std::vector(list[I], gen_vec<T, N, I + 1>(list, value)); 
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/gen_vec.cpp"

template <class T, size_t N, size_t I = 0>
decltype(auto) gen_vec(const size_t (&)[N], typename std::enable_if<(I == N), const T&>::type value = T{}) { 
  return value; 
}

template <class T, size_t N, size_t I = 0>
decltype(auto) gen_vec(const size_t (&list)[N], typename std::enable_if<(I != N), const T&>::type value = T{}) { 
  return std::vector(list[I], gen_vec<T, N, I + 1>(list, value)); 
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

