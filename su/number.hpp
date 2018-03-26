#pragma once

#include "type_list.hpp"
#include <ratio>
#include <cstdint>
#include <utility>

template<typename T>
struct is_ratio : public std::false_type {};

template<std::intmax_t Num, std::intmax_t Den>
struct is_ratio<std::ratio<Num, Den>> : public std::true_type {};

template<typename T>
constexpr bool is_ratio_v = is_ratio<T>::value;

template<typename T, typename Ratio>
constexpr auto apply_ratio(const T& value)
{
  static_assert(is_ratio_v<Ratio>, "Ratio must be of type std::ratio");
  return value * Ratio::num / Ratio::den;
}

template<typename SrcUnit, typename DestUnit>
struct converter {};

template<typename Unit>
struct converter<Unit, Unit>
{
  template<typename T>
  static constexpr T convert(const T& value) { return value; }
};

template<typename T, typename SrcUnit, typename DestUnit, typename = void>
struct is_convertible : public std::false_type {};

template<typename T, typename SrcUnit, typename DestUnit>
struct is_convertible<T, SrcUnit, DestUnit, std::void_t<decltype(converter<SrcUnit, DestUnit>::template convert<T>(std::declval<T>()))>> : public std::true_type {};

template<typename T, typename SrcUnit, typename DestUnit>
constexpr bool is_convertible_v = is_convertible<T, SrcUnit, DestUnit>::value;

template<typename T, typename Ratio, typename Unit>
class number;

template<typename T, typename Ratio = std::ratio<1>>
using unitless = number<T, Ratio, type_list<>>;

template<typename T>
struct is_unitless : public std::false_type {};

template<typename T, typename Ratio>
struct is_unitless<unitless<T, Ratio>> : public std::true_type {};

template<typename T>
constexpr bool is_unitless_v = is_unitless<T>::value;

template<typename T, typename Ratio, typename Unit>
class number
{
  static_assert(is_ratio_v<Ratio>, "Ratio must be of type std::ratio");

public:
  using value_type = T;
  using ratio = Ratio;
  using unit = Unit;
  using _type = number<T, Ratio, Unit>;

  template<typename U, typename = std::enable_if_t<std::is_constructible_v<T, U> && !is_unitless_v<_type>>>
  constexpr explicit number(U&& value)
    : _value(std::forward<U>(value))
  {}

  template<typename U, typename = std::enable_if_t<std::is_constructible_v<T, U> && is_unitless_v<_type>>, typename = void>
  constexpr number(U&& value)
    : _value(std::forward<U>(value))
  {}

  number(const number& other) = default;
  number& operator=(const number& other) = default;
  number(number&& other) = default;
  number& operator=(number&& other) = default;

  template<typename U, typename = std::enable_if_t<std::is_assignable_v<T&, U>>>
  number& operator=(U&& value)
  {
    _value = std::forward<U>(value);
    return *this;
  }

  constexpr T& value() { return _value; }
  constexpr const T& value() const { return _value; }

  constexpr explicit operator T&() { return value(); }
  constexpr explicit operator const T&() const { return value(); }

  template<typename U, typename DestRatio, typename DestUnit, typename = std::enable_if_t<std::is_constructible_v<U, T> && is_convertible_v<T, Unit, DestUnit>>>
  constexpr operator number<U, DestRatio, DestUnit>()
  {
      return number<U, DestRatio, DestUnit>(apply_ratio<T, std::ratio_divide<Ratio, DestRatio>>(converter<Unit, DestUnit>::template convert<T>(_value)));
  }

private:
  T _value;
};
