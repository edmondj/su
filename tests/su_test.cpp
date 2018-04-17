#include "catch.hpp"
#include "catch.hpp"
#include "su.hpp"


TEST_CASE("Length conversions")
{
  REQUIRE(su::meter<double>(su::inch<double>(42)).value() == 1.0668);
  REQUIRE(su::inch<double>(su::meter<double>(1.0668)).value() == 42);
  REQUIRE(su::meter<double>(su::foot<double>(42)).value() == Approx(12.8016));
  REQUIRE(su::foot<double>(su::meter<double>(12.8016)).value() == Approx(42));
  REQUIRE(su::meter<double>(su::yard<double>(42)).value() == Approx(38.4048));
  REQUIRE(su::yard<double>(su::meter<double>(38.4048)).value() == Approx(42));
}