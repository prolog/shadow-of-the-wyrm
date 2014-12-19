#include "Creature.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Trap.hpp"

using namespace std;

Trap::Trap() 
: Feature(MATERIAL_TYPE_IRON, ALIGNMENT_RANGE_NEUTRAL)
{
}

bool Trap::operator==(const Trap& trap) const
{
  return true;
}

Feature* Trap::clone()
{
  return new Trap(*this);
}

uchar Trap::get_symbol() const
{
  return '^';
}

string Trap::get_description_sid() const
{
  // JCD FIXME: Eventually, this should be a member variable
  // and settable via the constructor, etc.
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TRAP_GENERIC;
}

bool Trap::serialize(std::ostream& stream) const
{
  bool result = Feature::serialize(stream);
  return result;
}

bool Trap::deserialize(istream& stream)
{
  bool result = Feature::deserialize(stream);
  return result;
}

ClassIdentifier Trap::internal_class_identifier() const
{
  return CLASS_ID_TRAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/Trap_test.cpp"
#endif

