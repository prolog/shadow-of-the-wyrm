#include "Creature.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"
#include "Trap.hpp"

using namespace std;

Trap::Trap() 
: Feature(MATERIAL_TYPE_IRON, ALIGNMENT_RANGE_NEUTRAL)
{
}

bool Trap::operator==(const Trap& trap) const
{
  bool result = (description_sid == trap.description_sid);
  result = result && (trigger_message_sid == trap.trigger_message_sid);
  result = result && (damage == trap.damage);

  return result;
}

Trap* Trap::clone()
{
  return new Trap(*this);
}

uchar Trap::get_symbol() const
{
  return '^';
}

void Trap::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

void Trap::set_trigger_message_sid(const string& new_trigger_message_sid)
{
  trigger_message_sid = new_trigger_message_sid;
}

string Trap::get_trigger_message_sid() const
{
  return trigger_message_sid;
}

void Trap::set_damage(const Damage& new_damage)
{
  damage = new_damage;
}

Damage Trap::get_damage() const
{
  return damage;
}

string Trap::get_description_sid() const
{
  if (description_sid.empty())
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TRAP_GENERIC;
  }
  else
  {
    return description_sid;
  }
}

bool Trap::serialize(std::ostream& stream) const
{
  bool result = Feature::serialize(stream);

  Serialize::write_string(stream, description_sid);
  Serialize::write_string(stream, trigger_message_sid);
  damage.serialize(stream);

  return result;
}

bool Trap::deserialize(istream& stream)
{
  bool result = Feature::deserialize(stream);

  Serialize::read_string(stream, description_sid);
  Serialize::read_string(stream, trigger_message_sid);
  damage.deserialize(stream);

  return result;
}

ClassIdentifier Trap::internal_class_identifier() const
{
  return CLASS_ID_TRAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/Trap_test.cpp"
#endif

