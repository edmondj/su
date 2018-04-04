#include "composed_unit.hpp"

static_assert(std::is_same_v<int, su::simplify_type<su::type_list<int>>>);
static_assert(std::is_same_v<int, su::simplify_type<su::composed_unit<int, su::type_list<>>>>);
static_assert(std::is_same_v<int, su::simplify_type<su::composed_unit<su::type_list<int>, su::type_list<>>>>);
static_assert(std::is_same_v<int, su::simplify_type<su::composed_unit<su::type_list<int, int>, su::type_list<int>>>>);
static_assert(std::is_same_v<su::composed_unit<su::type_list<>, int>, su::simplify_type<su::composed_unit<su::type_list<int>, su::type_list<int, int>>>>);

static_assert(su::are_equivalent<
  su::composed_unit<su::type_list<int, short, float>, su::type_list<char, double>>,
  su::composed_unit<su::type_list<float, int, short>, su::type_list<double, char>>
>);

static_assert(std::is_same_v<su::type_list<int, short>, su::mul_type<int, short>>);
static_assert(std::is_same_v<su::type_list<int, short>, su::mul_type<su::type_list<int>, short>>);
static_assert(std::is_same_v<su::type_list<int, short>, su::mul_type<su::type_list<int>, su::type_list<short>>>);
static_assert(std::is_same_v<su::composed_unit<su::type_list<int, short>, char>, su::mul_type<su::composed_unit<int, char>, short>>);
static_assert(std::is_same_v<su::composed_unit<su::type_list<int, short, float>, char>, su::mul_type<su::composed_unit<su::type_list<int, short>, char>, float>>);

static_assert(std::is_same_v<su::div_type<int, int>, su::type_list<>>);