#pragma once

#include "number.hpp"

namespace su
{
#define SU_DECLARE_UNIT(unit) template<typename T, typename Ratio = std::ratio<1>> using unit = su::number<T, Ratio, struct unit ## _unit>;

#define SU_DECLARE_RATIO_UNIT(ratio, unit) template<typename T> using ratio ## unit = unit<T, std:: ## ratio>;

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

  SU_DECLARE_METRIC_UNIT(meter)

  template<>
  struct unit_metadata<meter_unit>
  {
    constexpr static const char* label = "m";
  };

}