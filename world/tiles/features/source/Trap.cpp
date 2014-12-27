#include "Creature.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"
#include "RNG.hpp"
#include "Trap.hpp"

using namespace std;

Trap::Trap() 
: Feature(MATERIAL_TYPE_IRON, ALIGNMENT_RANGE_NEUTRAL), triggered(false)
{
}

bool Trap::operator==(const Trap& trap) const
{
  bool result = (triggered == trap.triggered);
  result = result && (id == trap.id);
  result = result && (description_sid == trap.description_sid);
  result = result && (trigger_message_sid == trap.trigger_message_sid);
  result = result && (damage == trap.damage);

  return result;
}

Trap* Trap::clone()
{
  return new Trap(*this);
}

bool Trap::get_is_hidden() const
{
  return !triggered;
}

bool Trap::apply_on_movement(std::shared_ptr<Creature> creature) const
{
  bool apply_trap = true;

  // A successful detection check is required to not trigger a trap.
  int detection_value = creature->get_skills().get_value(SKILL_GENERAL_DETECTION);

  // If the trap has already been triggered, the creature has two
  // attempts to not set it off on movement, since its presence is
  // known.
  int num_chances = triggered ? 2 : 1;

  for (int i = 0; i < num_chances; i++)
  {
    if (RNG::percent_chance(detection_value))
    {
      apply_trap = false;
    }
  }

  return apply_trap;
}

uchar Trap::get_symbol() const
{
  return '^';
}

void Trap::set_triggered(const bool new_triggered)
{
  triggered = new_triggered;
}

bool Trap::get_triggered() const
{
  return triggered;
}

// Other features (fountains, fire pillars, etc) are class-based and 
// differentiated by their class ID. Traps are just configurations of a Trap 
// object, and are differentiated (arrow trap, fireball trap, etc) by their ID.
void Trap::set_id(const string& new_id)
{
  id = new_id;
}

string Trap::get_id() const
{
  return id;
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

  Serialize::write_bool(stream, triggered);
  Serialize::write_string(stream, id);
  Serialize::write_string(stream, description_sid);
  Serialize::write_string(stream, trigger_message_sid);
  damage.serialize(stream);

  return result;
}

bool Trap::deserialize(istream& stream)
{
  bool result = Feature::deserialize(stream);

  Serialize::read_bool(stream, triggered);
  Serialize::read_string(stream, id);
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

