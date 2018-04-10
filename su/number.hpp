#pragma once

#include "composed_unit.hpp"
#include <ratio>
#include <cstdint>
#include <utility>

namespace su
{

  template<typename T>
  constexpr bool is_ratio = false;

  template<std::intmax_t Num, std::intmax_t Den>
  constexpr bool is_ratio<std::ratio<Num, Den>> = true;

  template<typename Ratio, typename T>
  constexpr auto apply_ratio(const T& value)
  {
    static_assert(is_ratio<Ratio>, "Ratio must be of type std::ratio");
    return value * Ratio::num / Ratio::den;
  }

  template<typename SrcUnit, typename DestUnit, typename = void>
  struct converter {};

  template<typename SrcUnit, typename DestUnit>
  struct converter<SrcUnit, DestUnit, std::enable_if_t<are_equivalent<SrcUnit, DestUnit>>>
  {
    template<typename T>
    static constexpr T convert(const T& value) { return value; }
  };

  namespace detail
  {
    template<typename T, typename SrcUnit, typename DestUnit, typename = void>
    constexpr bool is_convertible = false;

    template<typename T, typename SrcUnit, typename DestUnit>
    constexpr bool is_convertible<T, SrcUnit, DestUnit, std::void_t<decltype(converter<SrcUnit, DestUnit>::convert(std::declval<T>()))>> = true;
  }

  template<typename T, typename SrcUnit, typename DestUnit>
  constexpr bool is_convertible = detail::is_convertible<T, SrcUnit, DestUnit>;

  template<typename Src, typename... Srcs, typename Dest, typename... Dests>
  struct converter<type_list<Src, Srcs...>, type_list<Dest, Dests...>, std::enable_if_t<sizeof...(Srcs) == sizeof...(Dests) && !are_equivalent<type_list<Src, Srcs...>, type_list<Dest, Dests...>>>>
  {
    template<typename T>
    static constexpr T convert(const T& value)
    {
      if constexpr (su::is_convertible<T, Src, Dest>)
        return converter<type_list<Srcs...>, type_list<Dests...>>::convert(converter<Src, Dest>::convert(value));
      else
        return converter<type_list<Src, Srcs...>, type_list<Dests..., Dest>>::convert(value);
    }
  };

  template<typename SrcNum, typename SrcDen, typename DestNum, typename DestDen>
  struct converter<composed_unit<SrcNum, SrcDen>, composed_unit<DestNum, DestDen>, std::enable_if_t<!are_equivalent<composed_unit<SrcNum, SrcDen>, composed_unit<DestNum, DestDen>>>>
  {
    template<typename T>
    static constexpr T convert(const T& value)
    {
      return converter<DestDen, SrcDen>::convert(converter<SrcNum, DestNum>::convert(value));
    }
  };

  using unitless_unit = type_list<>;

  template<typename T, typename Ratio, typename Unit>
  class number;

  template<typename T, typename Ratio = std::ratio<1>>
  using unitless = number<T, Ratio, unitless_unit>;
  
  template<typename T>
  constexpr bool is_unitless = false;

  template<typename T, typename Ratio>
  constexpr bool is_unitless<unitless<T, Ratio>> = true;

  template<typename T>
  constexpr bool is_number = false;

  template<typename T, typename Ratio, typename Unit>
  constexpr bool is_number<number<T, Ratio, Unit>> = true;

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
  constexpr bool is_value_constructible = !is_number<std::decay_t<U>> && std::is_constructible_v<T, U>;

  template<typename T, typename U>
  constexpr bool is_value_assignable = !is_number<std::decay_t<U>> && std::is_assignable_v<T&, U>;

  template<typename T, typename Ratio, typename Unit>
  class number
  {
    static_assert(is_ratio<Ratio>, "Ratio must be of type std::ratio");

  public:
    using value_type = T;
    using ratio = Ratio;
    using unit = Unit;

    number() = default;

    template<typename U, typename = std::enable_if_t<is_value_constructible<value_type, U> && !is_unitless<number>>>
    constexpr explicit number(U&& value)
      : _value(std::forward<U>(value))
    {}

    template<typename U, typename = std::enable_if_t<is_value_constructible<value_type, U> && is_unitless<number>>, typename = void>
    constexpr number(U&& value)
      : _value(std::forward<U>(value))
    {
      static_assert(is_value_constructible<value_type, U> && is_unitless<number>);
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

    template<typename U, typename DestRatio, typename DestUnit, typename = std::enable_if_t<std::is_constructible_v<U, value_type> && is_convertible<value_type, unit, DestUnit>>>
    constexpr operator number<U, DestRatio, DestUnit>() const
    {
      return number<U, DestRatio, DestUnit>(apply_ratio<std::ratio_divide<ratio, DestRatio>>(converter<unit, DestUnit>::convert(_value)));
    }

    template<typename U, typename = std::enable_if_t<!is_number<std::decay_t<U>> && std::is_constructible_v<U, value_type>>>
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

    template<bool condition = !is_unitless<number>, typename = std::enable_if_t<condition>>
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

    template<bool condition = !is_unitless<number>, typename = std::enable_if_t<condition>>
    constexpr number operator+(const unitless<value_type, ratio>& r) const
    {
      return number(value() + r.value());
    }

    template<typename U, typename RRatio, typename RUnit, bool condition = is_unitless<number> && !std::is_same_v<RUnit, unitless_unit>, typename = std::enable_if_t<condition>>
    constexpr number<U, RRatio, RUnit> operator+(const number<U, RRatio, RUnit>& r) const
    {
      return number<U, RRatio, RUnit>(apply_ratio<std::ratio_divide<ratio, RRatio>>(value()) + r.value());
    }

    constexpr number operator-(const number& r) const
    {
      return number(value() - r.value());
    }

    template<bool condition = !is_unitless<number>, typename = std::enable_if_t<condition>>
    constexpr number operator-(const unitless<value_type, ratio>& r) const
    {
      return number(value() - r.value());
    }

    template<typename U, typename RRatio, typename RUnit, bool condition = is_unitless<number> && !std::is_same_v<RUnit, unitless_unit>, typename = std::enable_if_t<condition>>
    constexpr number<U, RRatio, RUnit> operator-(const number<U, RRatio, RUnit>& r) const
    {
      return number<U, RRatio, RUnit>(apply_ratio<std::ratio_divide<ratio, RRatio>>(value()) - r.value());
    }

    template<typename U, typename RRatio, typename RUnit>
    constexpr auto operator*(const number<U, RRatio, RUnit>& other) const
    {
      return number<decltype(_value * other.value()), std::ratio_multiply<ratio, RRatio>, mul_unit<unit, RUnit>>(_value * other.value());
    };


    template<typename U, typename RRatio, typename RUnit>
    constexpr auto operator/(const number<U, RRatio, RUnit>& other) const
    {
      return number<decltype(_value / other.value()), std::ratio_divide<ratio, RRatio>, div_unit<unit, RUnit>>(_value / other.value());
    };

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

  template<typename U, typename T, typename Ratio, typename Unit, typename = std::enable_if_t<is_value_constructible<T, U>>>
  constexpr number<T, Ratio, Unit> operator-(U&& l, const number<T, Ratio, Unit>& r)
  {
    return number<T, Ratio, Unit>(std::forward<U>(l) - r.value());
  }

}
