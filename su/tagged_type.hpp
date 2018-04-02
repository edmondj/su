#pragma once

#include <utility>

namespace su
{

  template<typename T, typename>
  class tagged_type
  {
  public:
    explicit tagged_type(const T& value)
      : _value(value)
    {}

    explicit tagged_type(T&& value)
      : _value(std::move(value))
    {}

    tagged_type(const tagged_type&) = default;
    tagged_type& operator=(const tagged_type&) = default;
    tagged_type(tagged_type&&) = default;
    tagged_type& operator=(tagged_type&&) = default;

    T& get() { return _value; }
    const T& get() const { return _value; }

    explicit operator T&() { return get(); }
    explicit operator const T&() { return get(); }

  private:
    T _value;
  };

}
