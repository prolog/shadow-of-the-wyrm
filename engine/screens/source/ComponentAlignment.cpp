#include "ComponentAlignment.hpp"

ComponentAlignment::ComponentAlignment()
: override_default(false), value(0)
{
}

ComponentAlignment::ComponentAlignment(const bool new_override_default, const int new_value)
: override_default(new_override_default), value(new_value)
{
}

void ComponentAlignment::set_override_default(const bool new_override_default)
{
  override_default = new_override_default;
}

bool ComponentAlignment::get_override_default() const
{
  return override_default;
}

void ComponentAlignment::set_value(const int new_value)
{
  value = new_value;
}

int ComponentAlignment::get_value() const
{
  return value;
}

