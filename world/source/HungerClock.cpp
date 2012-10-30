#include "Conversion.hpp"
#include "HungerClock.hpp"
#include "Serialize.hpp"

using namespace std;

HungerClock::HungerClock()
: requires_food(false) /* Only player requires food, for now */, hunger(HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL)
{
}

// Set whether a food is required.  Initially, this should only be required
// of the player.
void HungerClock::set_requires_food(const bool food_required)
{
  requires_food = food_required;
}
 
bool HungerClock::get_requires_food() const
{
  return requires_food;
}

// Set/get the actual hunger level
void HungerClock::set_hunger(const int new_hunger)
{
  hunger = new_hunger;
}

int HungerClock::get_hunger() const
{
  return hunger;
}

// Check to see if the creature is so full that they cannot eat anything
// else.  Stuffed creatures obviously don't need to eat for a while, but
// they're naturally a lot slower, too.
bool HungerClock::is_stuffed() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HUNGER_LEVEL_STUFFED);
}

// Check to see if the creature is full.  Creatures that are full are a
// little slower than others.
bool HungerClock::is_full() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HUNGER_LEVEL_FULL);
}

// Check to see if the character is hungry.
bool HungerClock::is_hungry() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HUNGER_LEVEL_HUNGRY);
}

// Check to see if the character is starving (near death!)
bool HungerClock::is_starving() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HUNGER_LEVEL_STARVING);
}

// Uh oh!
bool HungerClock::is_dead() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HUNGER_LEVEL_DYING);
}

// Serialization details
bool HungerClock::serialize(ostream& stream)
{
  Serialize::write_bool(stream, requires_food);
  Serialize::write_int(stream, hunger);

  return true;
}

bool HungerClock::deserialize(istream& stream)
{
  Serialize::read_bool(stream, requires_food);
  Serialize::read_int(stream, hunger);

  return true;
}

ClassIdentifier HungerClock::internal_class_identifier() const
{
  return CLASS_ID_HUNGER_CLOCK;
}

#ifdef UNIT_TESTS
// JCD FIXME Add unit tests for hunger levels!
#endif
