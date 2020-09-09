#pragma once

#include <type_traits>
#include <utility>
#include <stdexcept>

template <class T, class = void>
class has_identity: public std::false_type { };

template <class T>
class has_identity<T, typename std::conditional<false, decltype(T::identity()), void>::type>: public std::true_type { };

template <class T>
constexpr typename std::enable_if<has_identity<T>::value, typename T::type>::type empty_exception() {
  return T::identity();
}
template <class T>
[[noreturn]] typename std::enable_if<!has_identity<T>::value, typename T::type>::type empty_exception() {
  throw std::runtime_error("type T has no identity");
}

template <class T, bool HasIdentity>
class fixed_monoid_impl: public T {
public:
  static constexpr typename T::type convert(const typename T::type &value) { return value; }
  static constexpr typename T::type revert(const typename T::type &value) { return value; }

  template <class Mapping, class Value, class... Args>
  static constexpr void operate(Mapping &&func, Value &value, const typename T::type &op, Args&&... args) {
    value = func(value, op, std::forward<Args>(args)...);
  }
};

template <class T>
class fixed_monoid_impl<T, false>: private T {
public:
  class type {
  public:
    typename T::type value;
    bool state;
  
    explicit constexpr type(): value(typename T::type { }), state(false) { }
    explicit constexpr type(const typename T::type &value): value(value), state(true) { }
  };

  static constexpr type convert(const typename T::type &value) { return type(value); }
  static constexpr typename T::type revert(const type &value) { 
    if (!value.state) throw std::runtime_error("attempted to revert identity to non-monoid"); 
    return value.value; 
  }

  static constexpr type identity() { return type(); }
  static constexpr type operation(const type &v1, const type &v2) {
    if (!v1.state) return v2;
    if (!v2.state) return v1;
    return type(T::operation(v1.value, v2.value));
  }

  template <class Mapping, class Value, class... Args>
  static constexpr void operate(Mapping &&func, Value &value, const type &op, Args&&... args) {
    if (!op.state) return;
    value = func(value, op, std::forward<Args>(args)...);
  }
};

template <class T>
using fixed_monoid = fixed_monoid_impl<T, has_identity<T>::value>;

/**
 * @title Monoid Utility
 */