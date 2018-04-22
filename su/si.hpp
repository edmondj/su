#pragma once

#include "su.hpp"

namespace su
{

  SU_DECLARE_METRIC_UNIT(meter)

  template<>
  struct unit_metadata<meter_unit>
  {
    constexpr static const char symbol = 'm';
  };

  SU_DECLARE_METRIC_LITERAL(meter, m)


  SU_DECLARE_METRIC_UNIT(gram)

  template<>
  struct unit_metadata<gram_unit>
  {
    constexpr static const char symbol = 'g';
  };

  SU_DECLARE_METRIC_LITERAL(gram, g)

  SU_DECLARE_UNIT(tonne)
  SU_BASIC_CONVERTER(tonne_unit, gram_unit, 1e6)
  template<>
  struct unit_metadata<tonne_unit>
  {
    constexpr static const char symbol = 't';
    using fallback_unit = gram_unit;
  };
  SU_DECLARE_LITERAL(tonne, t)

  SU_DECLARE_UNIT(atomic_mass)
  SU_BASIC_CONVERTER(atomic_mass_unit, gram_unit, 1.66e-24)
  template<>
  struct unit_metadata<atomic_mass_unit>
  {
    constexpr static const char symbol = 'u';
    using fallback_unit = gram_unit;
  };
  SU_DECLARE_LITERAL(atomic_mass, u)


  SU_DECLARE_METRIC_UNIT(second)
  template<>
  struct unit_metadata<second_unit>
  {
    constexpr static const char symbol = 's';
  };
  SU_DECLARE_METRIC_LITERAL(second, s)

  template<typename T>
  using minute = su::second<T, std::ratio<60>>;
  SU_DECLARE_LITERAL(minute, min)

  template<typename T>
  using hour = su::second<T, std::ratio<60 * 60>>;
  SU_DECLARE_LITERAL(hour, h)
}
