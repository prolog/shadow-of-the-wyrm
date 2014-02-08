#include "MaterialFactory.hpp"
#include "Pew.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Pew::Pew()
: Feature(MATERIAL_TYPE_WOOD)
{
}

Feature* Pew::clone()
{
  return new Pew(*this);
}

// Sit or stand, depending on the creature's current state.
bool Pew::handle(std::shared_ptr<Tile>, std::shared_ptr<Creature>)
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

float Pew::get_piety_loss_multiplier() const
{
  return 0.5f;
}

ClassIdentifier Pew::internal_class_identifier() const
{
  return CLASS_ID_PEW;
}

#ifdef UNIT_TESTS
#include "unit_tests/Pew_test.cpp"
#endif

