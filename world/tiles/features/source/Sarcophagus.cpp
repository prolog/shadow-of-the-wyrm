#include "Sarcophagus.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Sarcophagus::Sarcophagus()
: Feature(MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Sarcophagus::Sarcophagus(const MaterialType material_type)
: Feature(material_type, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

bool Sarcophagus::operator==(const Sarcophagus& sar) const
{
  bool result = Feature::operator==(sar);

  result = result && (inscription_sid == sar.inscription_sid);

  return result;
}

Feature* Sarcophagus::clone()
{
  return new Sarcophagus(*this);
}

uchar Sarcophagus::get_symbol() const
{
  return 'S';
}

pair<string, vector<string>> Sarcophagus::get_description_and_replacement_sids() const
{
  string message_sid = get_description_sid();

  vector<string> replacements;
  string inscription = get_inscription_sid();

  if (!inscription.empty())
  {
    replacements.push_back(inscription);
  }

  return make_pair(message_sid, replacements);
}

string Sarcophagus::get_description_sid() const
{
  if (!inscription_sid.empty())
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SARCOPHAGUS;
  }
  else
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SARCOPHAGUS_NO_INSCR;
  }
}

void Sarcophagus::set_inscription_sid(const string& new_inscription_sid)
{
  inscription_sid = new_inscription_sid;
}

string Sarcophagus::get_inscription_sid() const
{
  return inscription_sid;
}

bool Sarcophagus::serialize(ostream& stream) const
{
  Feature::serialize(stream);
  Serialize::write_string(stream, inscription_sid);

  return true;
}

bool Sarcophagus::deserialize(istream& stream)
{
  Feature::deserialize(stream);
  Serialize::read_string(stream, inscription_sid);

  return true;
}

ClassIdentifier Sarcophagus::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SARCOPHAGUS;
}

#ifdef UNIT_TESTS
#include "unit_tests/Sarcophagus_test.cpp"
#endif

