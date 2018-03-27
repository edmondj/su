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

static_assert(std::is_convertible_v<first_number<>, second_number<>> && std::is_convertible_v<second_number<>, first_number<>>);

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

TEST_CASE("Unit conversion")
{
  first_number<> first(42);
  second_number<> second = first;
  REQUIRE(second.value() == 42 * 13);

  second = second_number<>(1337);
  first = second;
  REQUIRE(first.value() == 1337.0 / 13.0);
}

TEST_CASE("Unit and ratio conversion")
{
  first_number<std::milli> first{ 2.0 };
  second_number<std::kilo> second = first;
  REQUIRE(second.value() == 2e-6 * 13);

  second = 0.5;
  first = second;
  REQUIRE(first.value() == 0.5e6 / 13);
}
