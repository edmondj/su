#include "tagged_type.hpp"
#include <functional>
#include <utility>

using type1 = tagged_type<int, struct type1tag>;

static_assert(std::is_constructible_v<type1, int>);
static_assert(!std::is_invocable_v<void(*)(type1), int>);
