#include "Fountain.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

Fountain::Fountain()
: Feature(MATERIAL_TYPE_MARBLE)
{
}

Feature* Fountain::clone()
{
  return new Fountain(*this);
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

#ifdef UNIT_TESTS
#include "unit_tests/Fountain_test.cpp"
#endif

