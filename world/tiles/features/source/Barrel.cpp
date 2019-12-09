#include "Barrel.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

const int Barrel::MIN_DRINKS = 3;
const int Barrel::MAX_DRINKS = 64;

Barrel::Barrel(const Symbol& new_symbol)
: Feature(MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), drinks(1), tap(false)
{
  initialize_drinks();
}

void Barrel::initialize_drinks()
{
  drinks = RNG::range(MIN_DRINKS, MAX_DRINKS);
}

Feature* Barrel::clone()
{
  return new Barrel(*this);
}

bool Barrel::operator==(const Barrel& b) const
{
  bool equal = true;

  equal = Feature::operator==(b);

  equal = equal && (drinks == b.drinks);
  equal = equal && (tap == b.tap);
  equal = equal && (pour_item_id == b.pour_item_id);

  return equal;
}

bool Barrel::pour()
{
  bool poured = false;

  if (can_pour())
  {
    drinks--;
    poured = true;
  }

  return poured;
}

bool Barrel::can_pour() const
{
  bool pour = false;

  if (tap && !pour_item_id.empty() && drinks > 0)
  {
    pour = true;
  }

  return pour;
}

string Barrel::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BARREL;
}

ClassIdentifier Barrel::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BARREL;
}

void Barrel::set_drinks(const int new_drinks)
{
  drinks = new_drinks;
}

int Barrel::get_drinks() const
{
  return drinks;
}

void Barrel::set_tap(const bool new_tap)
{
  tap = new_tap;
}

bool Barrel::get_tap() const
{
  return tap;
}

void Barrel::set_pour_item_id(const string& new_pour_item_id)
{
  pour_item_id = new_pour_item_id;
}

string Barrel::get_pour_item_id() const
{
  return pour_item_id;
}

bool Barrel::serialize(std::ostream& stream) const
{
  Feature::serialize(stream);

  Serialize::write_int(stream, drinks);
  Serialize::write_bool(stream, tap);
  Serialize::write_string(stream, pour_item_id);

  return true;
}

bool Barrel::deserialize(std::istream& stream)
{
  Feature::deserialize(stream);

  Serialize::read_int(stream, drinks);
  Serialize::read_bool(stream, tap);
  Serialize::read_string(stream, pour_item_id);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Barrel_test.cpp"
#endif

