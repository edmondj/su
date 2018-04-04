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
    struct simplify_type : public type_holder<T> {};
  }
}