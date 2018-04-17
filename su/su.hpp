#pragma once

#include "number.hpp"

namespace su
{
#define SU_DECLARE_UNIT(unit) template<typename T, typename Ratio = std::ratio<1>> using unit = su::number<T, Ratio, struct unit ## _unit>;

#define SU_DECLARE_RATIO_UNIT(ratio, unit) template<typename T> using ratio ## unit = unit<T, std:: ratio>;

#define SU_DECLARE_METRIC_UNIT(unit) \
SU_DECLARE_UNIT(unit) \
SU_DECLARE_RATIO_UNIT(atto, unit) \
SU_DECLARE_RATIO_UNIT(femto, unit) \
SU_DECLARE_RATIO_UNIT(pico, unit) \
SU_DECLARE_RATIO_UNIT(nano, unit) \
SU_DECLARE_RATIO_UNIT(micro, unit) \
SU_DECLARE_RATIO_UNIT(milli, unit) \
SU_DECLARE_RATIO_UNIT(centi, unit) \
SU_DECLARE_RATIO_UNIT(deci, unit) \
SU_DECLARE_RATIO_UNIT(deca, unit) \
SU_DECLARE_RATIO_UNIT(hecto, unit) \
SU_DECLARE_RATIO_UNIT(kilo, unit) \
SU_DECLARE_RATIO_UNIT(mega, unit) \
SU_DECLARE_RATIO_UNIT(giga, unit) \
SU_DECLARE_RATIO_UNIT(tera, unit) \
SU_DECLARE_RATIO_UNIT(peta, unit) \
SU_DECLARE_RATIO_UNIT(exa, unit)

#define SU_BASIC_CONVERTER(src_unit, dest_unit, ratio) \
template<> \
struct converter<src_unit, dest_unit> \
{\
  template<typename T> \
  static constexpr auto convert(T&& value) { return std::forward<T>(value) * ratio; } \
}; \
template<> \
struct converter<dest_unit, src_unit> \
{\
  template<typename T> \
  static constexpr auto convert(T&& value) { return std::forward<T>(value) / ratio; } \
};

  SU_DECLARE_METRIC_UNIT(meter)

  template<>
  struct unit_metadata<meter_unit>
  {
    constexpr static const char symbol = 'm';
  };

  SU_DECLARE_UNIT(inch)

  template<>
  struct unit_metadata<inch_unit>
  {
    constexpr static const char symbol = '"';
  };

  SU_BASIC_CONVERTER(inch_unit, meter_unit, 0.0254)


  SU_DECLARE_UNIT(foot)

  template<>
  struct unit_metadata<foot_unit>
  {
    constexpr static const char symbol = '\'';
    using fallback_unit = inch_unit;
  };

  SU_BASIC_CONVERTER(foot_unit, inch_unit, 12.0)


  SU_DECLARE_UNIT(yard)

  template<>
  struct unit_metadata<yard_unit>
  {
    constexpr static const char* symbol = "yd";
    using fallback_unit = foot_unit;
  };

  SU_BASIC_CONVERTER(yard_unit, foot_unit, 3)
}