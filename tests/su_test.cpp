#include "catch.hpp"
#include "catch.hpp"
#include "su.hpp"
#include "si.hpp"
#include "imperial.hpp"


using namespace su::literals;

TEST_CASE("Length conversions")
{
  REQUIRE(su::meter<double>(su::inch<double>(42)).value() == 1.0668);
  REQUIRE(su::inch<long double>(1.0668_m).value() == 42);
  REQUIRE(su::meter<double>(su::foot<double>(42)).value() == Approx(12.8016));
  REQUIRE(su::foot<long double>(12.8016_m).value() == Approx(42));
  REQUIRE(su::meter<double>(su::yard<double>(42)).value() == Approx(38.4048));
  REQUIRE(su::yard<long double>(38.4048_m).value() == Approx(42));
}