#include "Creature.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"
#include "RNG.hpp"
#include "Trap.hpp"

using namespace std;

Trap::Trap() 
: Feature(MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, 1 /* 1 use by default - will be set later */), triggered(false), trigger_symbol('?'), colour(Colour::COLOUR_WHITE)
{
}

bool Trap::operator==(const Trap& trap) const
{
  bool result = (Feature::operator==(trap));
  result = result && (triggered == trap.triggered);
  result = result && (id == trap.id);
  result = result && (description_sid == trap.description_sid);
  result = result && (trigger_message_sid == trap.trigger_message_sid);
  result = result && (trigger_symbol == trap.trigger_symbol);
  result = result && (player_damage_message_sid == trap.player_damage_message_sid);
  result = result && (colour == trap.colour);
  result = result && (item_id == trap.item_id);
  result = result && (damage == trap.damage);

  return result;
}

Trap* Trap::clone()
{
  return new Trap(*this);
}

Trap* Trap::clone_and_randomize_uses()
{
  Trap* trap = clone();

  if (trap)
  {
    // Jiggle the number of uses.
    int uses = trap->get_uses();

    if (uses > 1)
    {
      // 20% chance of +1 use.  5% chance of -1.
      if (RNG::percent_chance(20))
      {
        uses++;
      }
      else if (RNG::percent_chance(5))
      {
        uses--;
      }

      trap->set_uses(uses);
    }
  }

  return trap;
}

bool Trap::get_is_hidden() const
{
  return !triggered;
}

// Traps are dangerous.
// That's, uh, why we call them traps --
// only if triggered.
bool Trap::get_is_dangerous() const
{
  return triggered;
}

bool Trap::apply_on_movement(std::shared_ptr<Creature> creature) const
{
  bool apply_trap = true;

  // A successful detection check is required to not trigger a trap.
  int detection_value = creature->get_skills().get_value(SkillType::SKILL_GENERAL_DETECTION);

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

void Trap::set_trigger_symbol(const uchar new_trigger_symbol)
{
  trigger_symbol = new_trigger_symbol;
}

uchar Trap::get_trigger_symbol() const
{
  return trigger_symbol;
}

void Trap::set_player_damage_message_sid(const string& new_player_damage_message_sid)
{
  player_damage_message_sid = new_player_damage_message_sid;
}

string Trap::get_player_damage_message_sid() const
{
  return player_damage_message_sid;
}

void Trap::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Trap::get_colour() const
{
  return colour;
}

void Trap::set_item_id(const std::string& new_item_id)
{
  item_id = new_item_id;
}

string Trap::get_item_id() const
{
  return item_id;
}

bool Trap::has_items() const
{
  return (!item_id.empty() && (uses > 0));
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
  Serialize::write_uchar(stream, trigger_symbol);
  Serialize::write_string(stream, player_damage_message_sid);
  Serialize::write_enum(stream, colour);
  Serialize::write_string(stream, item_id);
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
  Serialize::read_uchar(stream, trigger_symbol);
  Serialize::read_string(stream, player_damage_message_sid);
  Serialize::read_enum(stream, colour);
  Serialize::read_string(stream, item_id);
  damage.deserialize(stream);

  return result;
}

ClassIdentifier Trap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TRAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/Trap_test.cpp"
#endif

