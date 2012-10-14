#include "Material.hpp"

using namespace std;

Colour Material::get_colour() const
{
  return COLOUR_WHITE;
}

// Material classes just return values from functions.  They're otherwise stateless,
// which is why these functions can be empty.
bool Material::serialize(ostream& stream)
{
  return true;
}

bool Material::deserialize(istream& stream)
{
  return true;
}

ClassIdentifier Material::internal_class_identifier() const
{
  return CLASS_ID_MATERIAL;
}