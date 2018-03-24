#pragma once

#include <type_traits>

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

template<typename Elem, typename List>
struct remove_one : public std::false_type
{
  using type = List;
};

template<typename Elem, typename... List>
struct remove_one<Elem, type_list<Elem, List...>> : public std::true_type
{
  using type = type_list<List...>;
};

template<typename Elem, typename Head, typename... Tail>
struct remove_one<Elem, type_list<Head, Tail...>> : public remove_one<Elem, type_list<Tail...>>
{
  using type = concat_types_t<Head, typename remove_one<Elem, type_list<Tail...>>::type>;
};

template<typename Elem, typename List>
using remove_one_t = typename remove_one<Elem, List>::type;

template<typename ToRemove, typename From>
struct complement_of
{
  using type = From;
};

template<typename ToRemove, typename... Tail, typename From>
struct complement_of<type_list<ToRemove, Tail...>, From>
{
  using type = typename complement_of<type_list<Tail...>, remove_one_t<ToRemove, From>>::type;
};

template<typename ToRemove, typename From>
using complement_of_t = typename complement_of<ToRemove, From>::type;