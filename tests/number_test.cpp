#include "number.hpp"
#include "catch.hpp"

using numberType1 = number<double, std::ratio<1>, struct numberType1Unit>;

//static_assert(std::is_constructible_v<numberType1, double>);
//static_assert(!std::is_invocable_v<void(*)(numberType1), double>);
//
//static_assert(std::is_constructible_v<unitless<double>, double>);
//static_assert(std::is_invocable_v<void(*)(unitless<double>), double>);

void foo()
{
  unitless<double> uless((double)(3.0));
}