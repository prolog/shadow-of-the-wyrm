#include "MaterialFactory.hpp"
#include "Pew.hpp"
#include "StringConstants.hpp"

using std::string;

Pew::Pew()
: Feature(MATERIAL_TYPE_WOOD)
{
}

// Sit or stand, depending on the creature's current state.
bool Pew::handle()
{
  return true;
}

// Destroy the pew.
bool Pew::kick()
{
  return true;
}

uchar Pew::get_symbol() const
{
  return '-';
}

string Pew::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PEW;
}

ClassIdentifier Pew::internal_class_identifier() const
{
  return CLASS_ID_PEW;
}