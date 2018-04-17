#pragma once

#include "type_list.hpp"

namespace su
{
  template<typename Num, typename Den>
  struct composed_unit
  {
    using num = Num;
    using den = Den;
  };

  namespace detail
  {
    template<typename T>
    struct is_composed : public std::false_type {};

    template<typename Num, typename Den>
    struct is_composed<composed_unit<Num, Den>> : public std::true_type {};
  }

  template<typename T>
  constexpr bool is_composed = detail::is_composed<T>::value;

  namespace detail
  {
    template<typename T>
    struct simplify_type : public type_holder<T> {};

    template<typename T>
    struct simplify_type<type_list<T>> : public type_holder<T> {};

    template<typename Num>
    struct simplify_type<composed_unit<Num, type_list<>>> : public type_holder<held_type<simplify_type<Num>>> {};

    template<typename Num, typename Den>
    struct inner_simplify_type : public type_holder<composed_unit<Num, Den>> {};

    template<typename Num>
    struct inner_simplify_type<Num, type_list<>> : public type_holder<Num> {};

    template<typename Num, typename Den>
    struct simplify_type<composed_unit<Num, Den>> : public inner_simplify_type<held_type<simplify_type<su::remove_type<Den, Num>>>, held_type<simplify_type<su::remove_type<Num, Den>>>> {};
  }

  template<typename T>
  using simplify_type = held_type<detail::simplify_type<T>>;

  namespace detail
  {
    template<typename L, typename R>
    struct are_equivalent : public std::is_same<L, R> {};
    
    template<typename... L, typename... R>
    struct are_equivalent<type_list<L...>, type_list<R...>> : public std::conjunction<
      std::is_same<type_list<>, su::remove_type<type_list<L...>, type_list<R...>>>,
      std::is_same<type_list<>, su::remove_type<type_list<R...>, type_list<L...>>>
    > {};

    template<typename LNum, typename LDen, typename RNum, typename RDen>
    struct are_equivalent<composed_unit<LNum, LDen>, composed_unit<RNum, RDen>> : public std::conjunction<are_equivalent<LNum, RNum>, are_equivalent<LDen, RDen>> {};
  }

  template<typename L, typename R>
  constexpr bool are_equivalent = detail::are_equivalent<L, R>::value;

  namespace detail
  {
    template<typename L, typename R>
    struct mul_unit : public type_holder<su::concat_types<L, R>> {};

    template<typename LNum, typename LDen, typename R>
    struct mul_unit<composed_unit<LNum, LDen>, R> : public simplify_type<composed_unit<su::concat_types<LNum, R>, LDen>> {};

    template<typename L, typename RNum, typename RDen>
    struct mul_unit<L, composed_unit<RNum, RDen>> : public simplify_type<composed_unit<su::concat_types<L, RNum>, RDen>> {};

    template<typename LNum, typename LDen, typename RNum, typename RDen>
    struct mul_unit<composed_unit<LNum, LDen>, composed_unit<RNum, RDen>> : public simplify_type<composed_unit<su::concat_types<LNum, RNum>, su::concat_types<LDen, RDen>>> {};
  }

  template<typename L, typename R>
  using mul_unit = held_type<detail::mul_unit<L, R>>;

  namespace detail
  {
    template<typename L, typename R>
    struct div_unit : public simplify_type<composed_unit<L, R>> {};

    template<typename LNum, typename LDen, typename R>
    struct div_unit<composed_unit<LNum, LDen>, R> : public simplify_type<composed_unit<LNum, su::concat_types<LDen, R>>> {};

    template<typename L, typename RNum, typename RDen>
    struct div_unit<L, composed_unit<RNum, RDen>> : public simplify_type<composed_unit<su::concat_types<L, RDen>, RNum>> {};

    template<typename LNum, typename LDen, typename RNum, typename RDen>
    struct div_unit<composed_unit<LNum, LDen>, composed_unit<RNum, RDen>> : public simplify_type<composed_unit<su::concat_types<LNum, RDen>, su::concat_types<LDen, RNum>>> {};
  }

  template<typename L, typename R>
  using div_unit = held_type<detail::div_unit<L, R>>;
}