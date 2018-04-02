#include "type_list.hpp"
#include <type_traits>

static_assert(std::is_same_v<su::concat_types_t<int, float>, su::type_list<int, float>>);
static_assert(std::is_same_v<su::concat_types_t<su::type_list<int, float>, double>, su::type_list<int, float, double>>);
static_assert(std::is_same_v<su::concat_types_t<char, su::type_list<int, float>>, su::type_list<char, int, float>>);
static_assert(std::is_same_v<su::concat_types_t<su::type_list<char, int>, su::type_list<float, double>>, su::type_list<char, int, float, double>>);


static_assert(std::is_same_v<su::remove_t<char, su::type_list<char, float>>, su::type_list<float>>);
static_assert(std::is_same_v<su::remove_t<int, su::type_list<int, char, float>>, su::type_list<char, float>>);
static_assert(std::is_same_v<su::remove_t<char, su::type_list<int, char, float>>, su::type_list<int, float>>);
static_assert(std::is_same_v<su::remove_t<su::type_list<int, short>, su::type_list<short, short, char, int, void*>>, su::type_list<short, char, void*>>);
static_assert(std::is_same_v<su::remove_t<su::type_list<short, short, char, int, void*>, su::type_list<int, short>>, su::type_list<>>);
