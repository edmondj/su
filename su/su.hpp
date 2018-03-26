#pragma once

#include "number.hpp"

template<typename T, typename Ratio = std::ratio<1>>
using meter = number<T, Ratio, struct meterUnit>;

template<typename T>
using kilometer = meter<T, std::kilo>;
