#pragma once

#include <type_traits>

namespace su
{

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

  template<typename ToRemove, typename From>
  struct remove
  {
    using type = From;
  };

  template<typename ToRemove, typename From>
  using remove_t = typename remove<ToRemove, From>::type;

  template<typename ToRemove, typename Head, typename... Tail>
  struct remove<ToRemove, type_list<Head, Tail...>>
  {
    using type = concat_types_t<Head, remove_t<ToRemove, type_list<Tail...>>>;
  };

  template<typename ToRemove, typename... Tail>
  struct remove<ToRemove, type_list<ToRemove, Tail...>>
  {
    using type = type_list<Tail...>;
  };

  template<typename HeadToRemove, typename... TailToRemove, typename Head, typename... Tail>
  struct remove<type_list<HeadToRemove, TailToRemove...>, type_list<Head, Tail...>>
  {
    using type = remove_t<type_list<TailToRemove...>, remove_t<HeadToRemove, type_list<Head, Tail...>>>;
  };

}
