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
    template<typename T>
    struct is_type_list : public std::false_type {};

    template<typename... T>
    struct is_type_list<type_list<T...>> : public std::true_type {};
  }

  template<typename T>
  constexpr const bool is_type_list = detail::is_type_list<T>::value;

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
    template<typename ToRemove, typename From, typename = void>
    struct remove_type : public std::conditional<std::is_same_v<ToRemove, From>, type_list<>, From> {};

    template<typename ToRemove, typename Head, typename... Tail>
    struct remove_type<ToRemove, type_list<Head, Tail...>> : public type_holder<su::concat_types<Head, held_type<remove_type<ToRemove, type_list<Tail...>>>>> {};

    template<typename ToRemove, typename... Tail>
    struct remove_type<ToRemove, type_list<ToRemove, Tail...>> : public type_holder<type_list<Tail...>> {};

    template<typename HeadToRemove, typename... TailToRemove, typename Head, typename... Tail>
    struct remove_type<type_list<HeadToRemove, TailToRemove...>, type_list<Head, Tail...>> : public type_holder<held_type<remove_type<type_list<TailToRemove...>, held_type<remove_type<HeadToRemove, type_list<Head, Tail...>>>>>> {};
  }

  template<typename ToRemove, typename From>
  using remove_type = held_type<detail::remove_type<ToRemove, From>>;

  namespace detail
  {
    template<typename T>
    struct type_list_head {};

    template<typename Head, typename... Tail>
    struct type_list_head<type_list<Head, Tail...>> : public type_holder<Head> {};
  }

  template<typename T>
  using type_list_head = held_type<detail::type_list_head<T>>;

  namespace detail
  {
    template<typename T>
    struct type_list_size : public std::integral_constant<std::size_t, 1> {};

    template<typename... T>
    struct type_list_size<type_list<T...>> : public std::integral_constant<std::size_t, sizeof...(T)> {};
  }

  template<typename T>
  constexpr const std::size_t type_list_size = detail::type_list_size<T>::value;
}
