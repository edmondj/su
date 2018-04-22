#include "catch.hpp"
#include "catch.hpp"
#include "su.hpp"
#include "si.hpp"
#include "imperial.hpp"
#include "si_derived.hpp"

using namespace su::literals;

TEST_CASE("Length conversions")
{
  REQUIRE(su::meter<long double>(42_in).value() == 1.0668);
  REQUIRE(su::inch<long double>(1.0668_m).value() == Approx(42));

  REQUIRE(su::meter<long double>(42_ft).value() == Approx(12.8016));
  REQUIRE(su::foot<long double>(12.8016_m).value() == Approx(42));

  REQUIRE(su::meter<long double>(42_yd).value() == Approx(38.4048));
  REQUIRE(su::yard<long double>(38.4048_m).value() == Approx(42));

  REQUIRE(su::kilometer<long double>(42_mi).value() == Approx(67.59245));
  REQUIRE(su::mile<long double>(67.59245_km).value() == Approx(42));

  REQUIRE(std::cos(su::radian<double>(su::pi<double> / 2.0)) == Approx(0).margin(1e-16));
  REQUIRE(std::cos(90.0_deg) == Approx(0).margin(1e-16));
}
