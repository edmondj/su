#pragma once

#include "si.hpp"

namespace su
{

  SU_DECLARE_UNIT(inch)

  template<>
  struct unit_metadata<inch_unit>
  {
    constexpr static const char symbol = '"';
  };

  SU_BASIC_CONVERTER(inch_unit, meter_unit, 0.0254)
  SU_DECLARE_LITERAL(inch, in)


  SU_DECLARE_UNIT(foot)

  template<>
  struct unit_metadata<foot_unit>
  {
    constexpr static const char symbol = '\'';
    using fallback_unit = inch_unit;
  };

  SU_BASIC_CONVERTER(foot_unit, inch_unit, 12.0)
  SU_DECLARE_LITERAL(foot, ft)


  SU_DECLARE_UNIT(yard)

  template<>
  struct unit_metadata<yard_unit>
  {
    constexpr static const char* symbol = "yd";
    using fallback_unit = foot_unit;
  };

  SU_BASIC_CONVERTER(yard_unit, foot_unit, 3)
  SU_DECLARE_LITERAL(yard, yd)

  
  SU_DECLARE_UNIT(mile)

  template<>
  struct unit_metadata<mile_unit>
  {
    constexpr static const char* symbol = "mi";
    using fallback_unit = yard_unit;
  };

  SU_BASIC_CONVERTER(mile_unit, yard_unit, 1760)
  SU_DECLARE_LITERAL(mile, mi)

  SU_DECLARE_UNIT(pound)
  SU_BASIC_CONVERTER(pound_unit, gram_unit, 453.59237)
  template<>
  struct unit_metadata<pound_unit>
  {
    constexpr static const char* symbol = "lb";
    using fallback_unit = gram_unit;
  };
  SU_DECLARE_LITERAL(pound, lb)

  template<typename T>
  using ounce = pound<T, std::ratio<1, 16>>;
  SU_DECLARE_LITERAL(ounce, oz)
}
