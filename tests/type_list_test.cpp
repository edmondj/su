#include "type_list.hpp"
#include <type_traits>

static_assert(std::is_same_v<concat_types_t<int, float>, type_list<int, float>>);
static_assert(std::is_same_v<concat_types_t<type_list<int, float>, double>, type_list<int, float, double>>);
static_assert(std::is_same_v<concat_types_t<char, type_list<int, float>>, type_list<char, int, float>>);
static_assert(std::is_same_v<concat_types_t<type_list<char, int>, type_list<float, double>>, type_list<char, int, float, double>>);


static_assert(std::is_same_v<remove_one_t<char, type_list<char, float>>, type_list<float>>);
static_assert(std::is_same_v<remove_one_t<int, type_list<int, char, float>>, type_list<char, float>>);
static_assert(std::is_same_v<remove_one_t<char, type_list<int, char, float>>, type_list<int, float>>);

static_assert(std::is_same_v<complement_of_t<type_list<char, int, float>, type_list<char, short, int, float>>, type_list<short>>);