#pragma once

#include <type_traits>

namespace su
{

  template<typename T>
  struct type_holder
  {
    using type = T;
  };

  template<typename T>
  using held_type = typename T::type;

  template<typename... Ts>
  struct type_list {};

  namespace detail
  {
    template<typename L, typename R>
    struct concat_types : public type_holder<type_list<L, R>> {};

    template<typename... L, typename R>
    struct concat_types<type_list<L...>, R> : public type_holder<type_list<L..., R>> {};

    template<typename L, typename... R>
    struct concat_types<L, type_list<R...>> : public type_holder<type_list<L, R...>> {};

    template<typename... L, typename... R>
    struct concat_types<type_list<L...>, type_list<R...>> : public type_holder<type_list<L..., R...>> {};
  }

  template<typename L, typename R> using concat_types = held_type<detail::concat_types<L, R>>;

  namespace detail
  {
    template<typename ToRemove, typename From>
    struct remove : public type_holder<From> {};

    template<typename ToRemove, typename Head, typename... Tail>
    struct remove<ToRemove, type_list<Head, Tail...>> : public type_holder<su::concat_types<Head, held_type<remove<ToRemove, type_list<Tail...>>>>> {};

    template<typename ToRemove, typename... Tail>
    struct remove<ToRemove, type_list<ToRemove, Tail...>> : public type_holder<type_list<Tail...>> {};

    template<typename HeadToRemove, typename... TailToRemove, typename Head, typename... Tail>
    struct remove<type_list<HeadToRemove, TailToRemove...>, type_list<Head, Tail...>> : public type_holder<held_type<remove<type_list<TailToRemove...>, held_type<remove<HeadToRemove, type_list<Head, Tail...>>>>>> {};
  }

  template<typename ToRemove, typename From>
  using remove = held_type<detail::remove<ToRemove, From>>;

}
