#include "EngineConversion.hpp"
#include "HungerClock.hpp"
#include "Serialize.hpp"

using namespace std;

const int HungerClock::MAX_HUNGER_VAL = 200000;

bool HungerClock::operator==(const HungerClock& hc) const
{
  bool result = true;

  result = result && (requires_food == hc.requires_food);
  result = result && (hunger == hc.hunger);

  return result;
}

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
  if (new_hunger > MAX_HUNGER_VAL)
  {
    hunger = MAX_HUNGER_VAL;
  }
  else if (new_hunger < 0)
  {
    hunger = 0;
  }
  else
  {
    hunger = new_hunger;
  }
}

int HungerClock::get_hunger() const
{
  return hunger;
}

bool HungerClock::can_eat(const int nutr) const
{
  if (is_stuffed())
  {
    return ((hunger + nutr < HungerLevelConverter::INT_HUNGER_LEVEL_COMPLETELY_FULL));
  }

  return true;
}

bool HungerClock::is_stomach_empty() const
{
  HungerLevel hl = HungerLevelConverter::to_hunger_level(hunger);

  return (hl == HungerLevel::HUNGER_LEVEL_DYING || hl == HungerLevel::HUNGER_LEVEL_STARVING || hl == HungerLevel::HUNGER_LEVEL_HUNGRY);
}

// Check to see if the creature is so full that they cannot eat anything
// else.  Stuffed creatures obviously don't need to eat for a while, but
// they're naturally a lot slower, too.
bool HungerClock::is_stuffed() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HungerLevel::HUNGER_LEVEL_STUFFED);
}

// Check to see if the creature is full.  Creatures that are full are a
// little slower than others.
bool HungerClock::is_full() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HungerLevel::HUNGER_LEVEL_FULL);
}

// Is everything peachy?
bool HungerClock::is_normal() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HungerLevel::HUNGER_LEVEL_NORMAL);
}

// Check to see if the character is hungry.
bool HungerClock::is_hungry() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HungerLevel::HUNGER_LEVEL_HUNGRY);
}

// Check to see if the character is starving (near death!)
bool HungerClock::is_starving() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HungerLevel::HUNGER_LEVEL_STARVING);
}

// Uh oh!
bool HungerClock::is_dying() const
{
  return (HungerLevelConverter::to_hunger_level(hunger) == HungerLevel::HUNGER_LEVEL_DYING);
}

// Is the character normal, hungry, starving, etc?
bool HungerClock::is_normal_or_worse() const
{
  HungerLevel hunger_l = HungerLevelConverter::to_hunger_level(hunger);

  return (hunger_l == HungerLevel::HUNGER_LEVEL_NORMAL
       || hunger_l == HungerLevel::HUNGER_LEVEL_HUNGRY
       || hunger_l == HungerLevel::HUNGER_LEVEL_STARVING
       || hunger_l == HungerLevel::HUNGER_LEVEL_DYING);
}

// Serialization details
bool HungerClock::serialize(ostream& stream) const
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
  return ClassIdentifier::CLASS_ID_HUNGER_CLOCK;
}

#ifdef UNIT_TESTS
#include "unit_tests/HungerClock_test.cpp"
#endif
