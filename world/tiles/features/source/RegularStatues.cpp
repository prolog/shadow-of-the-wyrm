#include "RegularStatues.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

RegularStatue::RegularStatue()
: Feature(MATERIAL_TYPE_STONE)
{
}

bool RegularStatue::kick()
{
  return true;
}

bool RegularStatue::handle()
{
  return true;
}

bool RegularStatue::get_is_blocking() const
{
  return true;
}

uchar RegularStatue::get_symbol() const
{
  return 'I';
}

ClassIdentifier RegularStatue::internal_class_identifier() const
{
  return CLASS_ID_REGULAR_STATUE;
}

// Petrified corpses
PetrifiedCorpseStatue::PetrifiedCorpseStatue()
: RegularStatue()
{
}

Feature* PetrifiedCorpseStatue::clone()
{
  return new PetrifiedCorpseStatue(*this);
}

string PetrifiedCorpseStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PETRIFIED_CORPSE_STATUE;
}

ClassIdentifier PetrifiedCorpseStatue::internal_class_identifier() const
{
  return CLASS_ID_PETRIFIED_CORPSE_STATUE;
}

#ifdef UNIT_TESTS
#include "unit_tests/RegularStatues_test.cpp"
#endif

