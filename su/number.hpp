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

template<typename Ratio, typename T>
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

using unitless_unit = type_list<>;

template<typename T, typename Ratio, typename Unit>
class number;

template<typename T, typename Ratio = std::ratio<1>>
using unitless = number<T, Ratio, unitless_unit>;

template<typename T>
struct is_unitless : public std::false_type {};

template<typename T, typename Ratio>
struct is_unitless<unitless<T, Ratio>> : public std::true_type {};

template<typename T>
constexpr bool is_unitless_v = is_unitless<T>::value;

template<typename T>
struct is_number : public std::false_type {};

template<typename T, typename Ratio, typename Unit>
struct is_number<number<T, Ratio, Unit>> : public std::true_type {};

template<typename T>
constexpr bool is_number_v = is_number<T>::value;

template<typename Unit>
struct unit_metadata
{
  constexpr static const char* label = "?";
};

template<>
struct unit_metadata<unitless_unit>
{
  constexpr static const char* label = "";
};

template<typename T, typename U>
constexpr bool is_value_constructible = !is_number_v<std::decay_t<U>> && std::is_constructible_v<T, U>;

template<typename T, typename U>
constexpr bool is_value_assignable = !is_number_v<std::decay_t<U>> && std::is_assignable_v<T&, U>;

template<typename T, typename Ratio, typename Unit>
class number
{
  static_assert(is_ratio_v<Ratio>, "Ratio must be of type std::ratio");

public:
  using value_type = T;
  using ratio = Ratio;
  using unit = Unit;

  number() = default;

  template<typename U, typename = std::enable_if_t<is_value_constructible<value_type, U> && !is_unitless_v<number>>>
  constexpr explicit number(U&& value)
    : _value(std::forward<U>(value))
  {}

  template<typename U, typename = std::enable_if_t<is_value_constructible<value_type, U> && is_unitless_v<number>>, typename = void>
  constexpr number(U&& value)
    : _value(std::forward<U>(value))
  {
    static_assert(is_value_constructible<value_type, U> && is_unitless_v<number>);
  }

  number(const number& other) = default;
  number& operator=(const number& other) = default;
  number(number&& other) = default;
  number& operator=(number&& other) = default;

  template<typename U, typename = std::enable_if_t<is_value_assignable<value_type, U>>>
  number& operator=(U&& value)
  {
    _value = std::forward<U>(value);
    return *this;
  }

  constexpr value_type& value() { return _value; }
  constexpr const value_type& value() const { return _value; }

  template<typename U, typename DestRatio, typename DestUnit, typename = std::enable_if_t<std::is_constructible_v<U, value_type> && is_convertible_v<value_type, unit, DestUnit>>>
  constexpr operator number<U, DestRatio, DestUnit>() const
  {
    return number<U, DestRatio, DestUnit>(apply_ratio<std::ratio_divide<ratio, DestRatio>>(converter<unit, DestUnit>::convert(_value)));
  }

  template<typename U, typename = std::enable_if_t<!is_number_v<std::decay_t<U>> && std::is_constructible_v<U, value_type>>>
  constexpr explicit operator U() const
  {
    return _value;
  }

  constexpr number& operator+=(const number& r)
  {
    _value += r.value();
    return *this;
  }

  template<bool condition = !std::is_same_v<number, unitless<value_type, ratio>>, typename = std::enable_if_t<condition>>
  constexpr number& operator+=(const unitless<value_type, ratio>& r)
  {
    _value += r.value();
    return *this;
  }

  constexpr number& operator-=(const number& r)
  {
    _value -= r.value();
    return *this;
  }

  template<bool condition = !is_unitless_v<number>, typename = std::enable_if_t<condition>>
  constexpr number& operator-=(const unitless<value_type, ratio>& r)
  {
    _value -= r.value();
    return *this;
  }

  constexpr number& operator*=(const unitless<value_type, ratio>& r)
  {
    _value *= r.value();
    return *this;
  }

  constexpr number& operator/=(const unitless<value_type, ratio>& r)
  {
    _value /= r.value();
    return *this;
  }

  constexpr number& operator++()
  {
    ++_value;
    return *this;
  }

  constexpr number& operator--()
  {
    --_value;
    return *this;
  }

  constexpr number operator++(int)
  {
    number sent(_value);
    ++_value;
    return sent;
  }

  constexpr number operator--(int)
  {
    number sent(_value);
    --_value;
    return sent;
  }

  constexpr auto operator+() const { return number<decltype(+_value), ratio, unit>(+_value); }
  constexpr auto operator-() const { return number<decltype(-_value), ratio, unit>(-_value); }

  constexpr number operator+(const number& r) const
  {
    return number(value() + r.value());
  }

  template<bool condition = !is_unitless_v<number>, typename = std::enable_if_t<condition>>
  constexpr number operator+(const unitless<value_type, ratio>& r) const
  {
    return number(value() + r.value());
  }

  template<typename U, typename Ratio2, typename Unit2, bool condition = is_unitless_v<number> && !std::is_same_v<Unit2, unitless_unit>, typename = std::enable_if_t<condition>>
  constexpr number<U, Ratio2, Unit2> operator+(const number<U, Ratio2, Unit2>& r) const
  {
    return number<U, Ratio2, Unit2>(apply_ratio<std::ratio_divide<ratio, Ratio2>>(value()) + r.value());
  }

  //T T::operator-(const T2 &b) const;
  //T T::operator*(const T2 &b) const;
  //T T::operator/(const T2 &b) const;

  constexpr auto operator==(const number& other) const { return value() == other.value(); }
  constexpr auto operator!=(const number& other) const { return value() != other.value(); }
  constexpr auto operator<(const number& other) const { return value() < other.value(); }
  constexpr auto operator>(const number& other) const { return value() > other.value(); }
  constexpr auto operator<=(const number& other) const { return value() <= other.value(); }
  constexpr auto operator>=(const number& other) const { return value() >= other.value(); }

private:
  value_type _value;
};

template<typename U, typename T, typename Ratio, typename Unit, typename = std::enable_if_t<is_value_constructible<T, U>>>
constexpr number<T, Ratio, Unit> operator+(U&& l, const number<T, Ratio, Unit>& r)
{
  return number<T, Ratio, Unit>(std::forward<U>(l) + r.value());
}
