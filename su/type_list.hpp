#pragma once

#include <type_traits>

namespace su
{

  template<typename... Ts>
  struct type_list {};

  namespace detail
  {
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
  }

  template<typename L, typename R> using concat_types = typename detail::concat_types<L, R>::type;

  namespace detail
  {
    template<typename ToRemove, typename From>
    struct remove
    {
      using type = From;
    };

    template<typename ToRemove, typename Head, typename... Tail>
    struct remove<ToRemove, type_list<Head, Tail...>>
    {
      using type = su::concat_types<Head, typename remove<ToRemove, type_list<Tail...>>::type>;
    };

    template<typename ToRemove, typename... Tail>
    struct remove<ToRemove, type_list<ToRemove, Tail...>>
    {
      using type = type_list<Tail...>;
    };

    template<typename HeadToRemove, typename... TailToRemove, typename Head, typename... Tail>
    struct remove<type_list<HeadToRemove, TailToRemove...>, type_list<Head, Tail...>>
    {
      using type = typename remove<type_list<TailToRemove...>, typename remove<HeadToRemove, type_list<Head, Tail...>>::type>::type;
    };
  }

  template<typename ToRemove, typename From>
  using remove = typename detail::remove<ToRemove, From>::type;

}
