#include "number.hpp"
#include "catch.hpp"
#include "ionumber.hpp"

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

static_assert(std::is_same_v<typename decltype(+std::declval<number<char, std::ratio<1>, struct tmp_unit>>())::value_type, decltype(+std::declval<char>())>);

TEST_CASE("Unary operators")
{
  REQUIRE((+first_number<>(-2)).value() == -2);
  REQUIRE((-first_number<>(-2)).value() == 2);
}

TEST_CASE("Comparaison")
{
  first_number<std::milli> milli(1000);
  first_number<std::kilo> kilo = milli;
  second_number<> ref(1);

  REQUIRE(milli == milli);
  REQUIRE(milli == kilo);
  REQUIRE(kilo == milli);
  REQUIRE(kilo != ref);
  REQUIRE(ref != kilo);
  REQUIRE(ref < kilo);
  REQUIRE(kilo > ref);
  REQUIRE(ref <= kilo);
  REQUIRE(kilo <= milli);
  REQUIRE(kilo >= ref);
  REQUIRE(kilo >= milli);
}

static_assert(!is_unitless_v<first_number<std::milli>>);

TEST_CASE("Unitless")
{
  unitless<double, std::ratio<1>> unit(3.0);
  unitless<double, std::kilo> kilo = unit;
  REQUIRE(kilo.value() == 3e-3);

  unitless<double, std::milli> milli = kilo;
  REQUIRE(milli.value() == 3e3);

  milli = 13;
  unit = milli;
  REQUIRE(unit.value() == 13e-3);
}

static_assert(!is_value_constructible<double, number<double, std::ratio<1, 1>, type_list<>>>);

TEST_CASE("Assignments")
{
  first_number<std::milli> milli(1000);
  unitless<double> uless(10);

  milli += milli;
  REQUIRE(milli.value() == 2000);
  milli -= milli;
  REQUIRE(milli.value() == 0);
  milli = 1000;

  milli += 3;
  REQUIRE(milli.value() == 1003);
  uless += 1;
  REQUIRE(uless.value() == 11);
  milli += uless;
  REQUIRE(milli.value() == 12003);

  milli -= uless;
  REQUIRE(milli.value() == 1003);
  uless -= 1;
  REQUIRE(uless.value() == 10);
  milli -= 3;
  REQUIRE(milli.value() == 1000);

  milli *= 2;
  REQUIRE(milli.value() == 2000);
  uless *= 0.0003;
  REQUIRE(uless.value() == Approx(0.003));
  milli *= uless;
  REQUIRE(milli.value() == Approx(6000));

  milli /= uless;
  REQUIRE(milli.value() == Approx(2000));
  uless /= 0.0003;
  REQUIRE(uless.value() == 10);
  milli /= 2;
  REQUIRE(milli.value() == 1000);
}