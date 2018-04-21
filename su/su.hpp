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

#define SU_DECLARE_LITERAL(unit, symbol) \
namespace literals \
{ \
  unit<unsigned long long int> operator ""_ ## symbol (unsigned long long int value) { return unit<unsigned long long int>(value); } \
  unit<long double> operator ""_ ## symbol (long double value) { return unit<long double>(value); } \
}

#define SU_DECLARE_METRIC_LITERAL(unit, symbol) \
SU_DECLARE_LITERAL(unit, symbol) \
SU_DECLARE_LITERAL(atto ## unit, a ## symbol) \
SU_DECLARE_LITERAL(femto ## unit, f ## symbol) \
SU_DECLARE_LITERAL(pico ## unit, p ## symbol) \
SU_DECLARE_LITERAL(nano ## unit, n ## symbol) \
SU_DECLARE_LITERAL(micro ## unit, μ ## symbol) \
SU_DECLARE_LITERAL(milli ## unit, m ## symbol) \
SU_DECLARE_LITERAL(centi ## unit, c ## symbol) \
SU_DECLARE_LITERAL(deci ## unit, d ## symbol) \
SU_DECLARE_LITERAL(deca ## unit, da ## symbol) \
SU_DECLARE_LITERAL(hecto ## unit, h ## symbol) \
SU_DECLARE_LITERAL(kilo ## unit, k ## symbol) \
SU_DECLARE_LITERAL(mega ## unit, M ## symbol) \
SU_DECLARE_LITERAL(giga ## unit, G ## symbol) \
SU_DECLARE_LITERAL(tera ## unit, T ## symbol) \
SU_DECLARE_LITERAL(peta ## unit, P ## symbol) \
SU_DECLARE_LITERAL(exa ## unit, E ## symbol)


}