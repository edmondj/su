#include "type_list.hpp"
#include <type_traits>

static_assert(std::is_same_v<su::concat_types<int, float>, su::type_list<int, float>>);
static_assert(std::is_same_v<su::concat_types<su::type_list<int, float>, double>, su::type_list<int, float, double>>);
static_assert(std::is_same_v<su::concat_types<char, su::type_list<int, float>>, su::type_list<char, int, float>>);
static_assert(std::is_same_v<su::concat_types<su::type_list<char, int>, su::type_list<float, double>>, su::type_list<char, int, float, double>>);


static_assert(std::is_same_v<su::remove_type<int, char>, char>);
static_assert(std::is_same_v<su::remove_type<int, int>, su::type_list<>>);
static_assert(std::is_same_v<su::remove_type<int, su::type_list<int, char>>, su::type_list<char>>);
static_assert(std::is_same_v<su::remove_type<su::type_list<int, char>, su::type_list<char, int>>, su::type_list<>>);
static_assert(std::is_same_v<su::remove_type<su::type_list<int, char>, su::type_list<int, char>>, su::type_list<>>);
static_assert(std::is_same_v<su::remove_type<su::type_list<int, char>, su::type_list<int, short, char>>, su::type_list<short>>);
static_assert(std::is_same_v<su::remove_type<su::type_list<int, short, char>, su::type_list<int, char>>, su::type_list<>>);
