#include "Fountain.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

Fountain::Fountain()
: Feature(MATERIAL_TYPE_MARBLE)
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

string Fountain::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FOUNTAIN;
}

ClassIdentifier Fountain::internal_class_identifier() const
{
  return CLASS_ID_FOUNTAIN;
}