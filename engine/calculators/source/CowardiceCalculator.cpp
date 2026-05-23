#include "CowardiceCalculator.hpp"
#include "CreatureProperties.hpp"

const int CowardiceCalculator::BASE_PCT_CHANCE_TURN_TO_FIGHT = 10;
const int CowardiceCalculator::BASE_PCT_CHANCE_RAGE_FIGHT = 10;
std::map<CreatureSize, int> CowardiceCalculator::TURN_TO_FIGHT = {};
std::map<CreatureSize, int> CowardiceCalculator::RAGE_FIGHT = {};

CowardiceCalculator::CowardiceCalculator()
{
  if (TURN_TO_FIGHT.empty() || RAGE_FIGHT.empty())
  {
    initialize();
  }
}

void CowardiceCalculator::initialize()
{
  TURN_TO_FIGHT = { {CreatureSize::CREATURE_SIZE_TINY, 4},
                    {CreatureSize::CREATURE_SIZE_SMALL, 8},
                    {CreatureSize::CREATURE_SIZE_MEDIUM, 10},
                    {CreatureSize::CREATURE_SIZE_LARGE, 15},
                    {CreatureSize::CREATURE_SIZE_HUGE, 20},
                    {CreatureSize::CREATURE_SIZE_BEHEMOTH, 25} };

  RAGE_FIGHT = { {CreatureSize::CREATURE_SIZE_TINY, 4},
                 {CreatureSize::CREATURE_SIZE_SMALL, 8},
                 {CreatureSize::CREATURE_SIZE_MEDIUM, 10},
                 {CreatureSize::CREATURE_SIZE_LARGE, 15},
                 {CreatureSize::CREATURE_SIZE_HUGE, 20},
                 {CreatureSize::CREATURE_SIZE_BEHEMOTH, 25} };
}

int CowardiceCalculator::get_pct_chance_turn_to_fight(CreaturePtr creature) const
{
  int chance = BASE_PCT_CHANCE_TURN_TO_FIGHT;

  if (creature != nullptr && creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_PERMANENT_COWARD))
  {
    chance = 0;
  }

  if (creature != nullptr)
  {
    auto ttf_it = TURN_TO_FIGHT.find(creature->get_size());

    if (ttf_it != TURN_TO_FIGHT.end())
    {
      chance = ttf_it->second;
    }
  }

  return chance;
}

int CowardiceCalculator::get_pct_chance_rage_fight(CreaturePtr creature) const
{
  int chance = BASE_PCT_CHANCE_RAGE_FIGHT;

  if (creature != nullptr && creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_PERMANENT_COWARD))
  {
    chance = 0;
  }

  if (creature != nullptr)
  {
    auto rage_it = RAGE_FIGHT.find(creature->get_size());

    if (rage_it != RAGE_FIGHT.end())
    {
      chance = rage_it->second;
    }
  }

  return chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/CowardiceCalculator_test.cpp"
#endif

