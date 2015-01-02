#include "RegularStatues.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

RegularStatue::RegularStatue()
: Feature(MATERIAL_TYPE_STONE, ALIGNMENT_RANGE_NEUTRAL)
{
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
  return ClassIdentifier::CLASS_ID_REGULAR_STATUE;
}

// Petrified corpses
PetrifiedCorpseStatue::PetrifiedCorpseStatue()
: RegularStatue()
{
}

PetrifiedCorpseStatue::PetrifiedCorpseStatue(const string& corpse_sid)
: corpse_description_sid(corpse_sid)
{
}

bool PetrifiedCorpseStatue::operator==(const PetrifiedCorpseStatue& pcs) const
{
  bool result = RegularStatue::operator==(pcs);

  result = result && (corpse_description_sid == pcs.corpse_description_sid);

  return result;
}

void PetrifiedCorpseStatue::set_corpse_description_sid(const string& new_corpse_description_sid)
{
  corpse_description_sid = new_corpse_description_sid;
}

string PetrifiedCorpseStatue::get_corpse_description_sid() const
{
  return corpse_description_sid;
}

pair<string, vector<string>> PetrifiedCorpseStatue::get_description_and_replacement_sids() const
{
  vector<string> replacement_sids;
  string description_sid = get_description_sid();

  if (!corpse_description_sid.empty())
  {
    replacement_sids.push_back(corpse_description_sid);
  }

  return make_pair(description_sid, replacement_sids);
}

Feature* PetrifiedCorpseStatue::clone()
{
  return new PetrifiedCorpseStatue(*this);
}

bool PetrifiedCorpseStatue::serialize(ostream& stream) const
{
  RegularStatue::serialize(stream);
  Serialize::write_string(stream, corpse_description_sid);

  return true;
}

bool PetrifiedCorpseStatue::deserialize(istream& stream)
{
  RegularStatue::deserialize(stream);
  Serialize::read_string(stream, corpse_description_sid);

  return true;
}

string PetrifiedCorpseStatue::get_description_sid() const
{
  if (!corpse_description_sid.empty())
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PETRIFIED_CORPSE_STATUE_WITH_DESC;
  }
  else
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PETRIFIED_CORPSE_STATUE;
  }
}

ClassIdentifier PetrifiedCorpseStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE;
}

#ifdef UNIT_TESTS
#include "unit_tests/RegularStatues_test.cpp"
#endif

