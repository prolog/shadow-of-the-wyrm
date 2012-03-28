#include "Fountain.hpp"
#include "MaterialFactory.hpp"

Fountain::Fountain()
: Feature(MaterialFactory::create_material(MATERIAL_TYPE_MARBLE))
{
}

bool Fountain::handle()
{
  return true;
}

bool Fountain::kick()
{
  return true;
}

uchar Fountain::get_symbol() const
{
  return '~';
}
