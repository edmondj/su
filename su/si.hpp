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

}