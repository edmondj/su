#include "number.hpp"
#include "catch.hpp"

using number_type_1 = number<double, std::ratio<1>, struct numberType1Unit>;

static_assert(std::is_constructible_v<number_type_1, double>);
static_assert(!std::is_invocable_v<void(*)(number_type_1), double>);

static_assert(std::is_constructible_v<unitless<double>, double>);
static_assert(std::is_invocable_v<void(*)(unitless<double>), double>);

template<typename Ratio = std::ratio<1>>
using first_number = number<double, Ratio, struct first_unit>;


template<typename Ratio = std::ratio<1>>
using second_number = number<double, Ratio, struct second_unit>;

template<>
struct converter<first_number<>::unit, second_number<>::unit>
{
  template<typename T>
  constexpr static T convert(const T& value) { return value * 13; }
};

template<>
struct converter<second_number<>::unit, first_number<>::unit>
{
  template<typename T>
  constexpr static T convert(const T& value) { return value / 13; }
};

TEST_CASE("Same unit ratio conversion")
{
  first_number<std::ratio<1>> unit(3.0);
  first_number<std::kilo> kilo = unit;
  REQUIRE(kilo.value() == 3e-3);

  first_number<std::milli> milli = kilo;
  REQUIRE(milli.value() == 3e3);

  milli = 13;
  unit = milli;
  REQUIRE(unit.value() == 13e-3);
}