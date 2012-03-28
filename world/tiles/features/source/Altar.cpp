#include "Altar.hpp"

Altar::Altar(const std::string& new_deity_id, MaterialPtr new_material)
: Feature(new_material), deity_id(new_deity_id)
{
}

bool Altar::handle()
{
  return offer();
}

bool Altar::kick()
{
  // Bad things happen.
  return true;
}

bool Altar::offer()
{
  // Good things happen.
  return true;
}

uchar Altar::get_symbol() const
{
  return '_';
}
