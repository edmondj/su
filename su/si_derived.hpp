#pragma once

#include <cmath>
#include "si.hpp"

namespace su
{
  template<typename T>
  constexpr T pi = T(3.141592653589793238462643383);

  SU_DECLARE_UNIT(radian)
  template<>
  struct unit_metadata<radian_unit>
  {
    constexpr static const char* symbol = "rad";
  };
  SU_DECLARE_LITERAL(radian, rad)

  SU_DECLARE_UNIT(degree)
  template<>
  struct unit_metadata<degree_unit>
  {
    constexpr static const char* symbol = "deg";
  };
  SU_DECLARE_LITERAL(degree, deg)

  SU_BASIC_CONVERTER(radian_unit, degree_unit, 180.0 / pi<T>)
}

namespace std
{
  template<typename T, typename = std::enable_if_t<su::is_convertible<typename T::value_type, typename T::unit, su::radian_unit>>>
  auto cos(const T& angle)
  {
    return std::cos(su::radian<typename T::value_type>(angle).value());
  }
  
  template<typename T, typename = std::enable_if_t<su::is_convertible<typename T::value_type, typename T::unit, su::radian_unit>>>
  auto sin(const T& angle)
  {
    return std::sin(su::radian<typename T::value_type>(angle).value());
  }

  template<typename T, typename = std::enable_if_t<su::is_convertible<typename T::value_type, typename T::unit, su::radian_unit>>>
  auto tan(const T& angle)
  {
    return std::tan(su::radian<typename T::value_type>(angle).value());
  }
}
