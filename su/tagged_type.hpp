#pragma once

#include <utility>

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

  T& get() { return _value; }
  const T& get() const { return _value; }

  explicit operator T&() { return get(); }
  explicit operator const T&() { return get(); }

private:
  T _value;
};
