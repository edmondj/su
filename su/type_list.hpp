#pragma once

template<typename... Ts>
struct type_list {};

template<typename L, typename R>
struct concat_types
{
  using type = type_list<L, R>;
};

template<typename... L, typename R>
struct concat_types<type_list<L...>, R>
{
  using type = type_list<L..., R>;
};

template<typename L, typename... R>
struct concat_types<L, type_list<R...>>
{
  using type = type_list<L, R...>;
};

template<typename... L, typename... R>
struct concat_types<type_list<L...>, type_list<R...>>
{
  using type = type_list<L..., R...>;
};

template<typename L, typename R> using concat_types_t = typename concat_types<L, R>::type;