#pragma once

#include "number.hpp"
#include <iostream>

//template<typename Ratio, typename CharT, typename Traits>
//std::basic_ostream<CharT, Traits>& display_ratio(std::basic_ostream<CharT, Traits>& out)
//{
//  static_assert(is_ratio_v<Ratio>);
//  return out << '{' << Ratio::num << '/' << Ratio::den << '}';
//}
//
//template<typename CharT, typename Traits>
//std::basic_ostream<CharT, Traits>& display_ratio<std::kilo, CharT, Traits>(std::basic_ostream<CharT, Traits>& out)
//{
//  return out << 'k';
//}

template<typename Ratio, typename CharT, typename Traits>
constexpr auto display_ratio = [](std::basic_ostream<CharT, Traits>& out) -> std::basic_ostream<CharT, Traits>&
{
  static_assert(is_ratio_v<Ratio>);
  return out << '{' << Ratio::num << '/' << Ratio::den << '}';
};

#define DISPLAY_RATIO(Ratio) \
template<typename CharT, typename Traits> \
constexpr auto display_ratio<Ratio, CharT, Traits> = [](std::basic_ostream<CharT, Traits>& out) -> std::basic_ostream<CharT, Traits>&

DISPLAY_RATIO(std::kilo)
{
  return out << 'k';
};

DISPLAY_RATIO(std::milli)
{
  return out << 'm';
};

DISPLAY_RATIO(std::ratio<1>)
{
  return out;
};

template<typename CharT, typename Traits, typename T, typename Ratio, typename Unit>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& out, const number<T, Ratio, Unit>& n)
{
  return out << n.value() << display_ratio<Ratio, CharT, Traits> << unit_metadata<Unit>::label;
}
