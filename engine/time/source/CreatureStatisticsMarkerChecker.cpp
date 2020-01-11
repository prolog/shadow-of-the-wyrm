#include "CreatureStatisticsMarkerChecker.hpp"
#include "EngineConversion.hpp"
#include "HungerCalculator.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"
#include "StatisticsMarker.hpp"

using namespace std;

const int CreatureStatisticsMarkerChecker::PASSIVE_STATISTIC_THRESHOLD = 15;

CreatureStatisticsMarkerChecker::CreatureStatisticsMarkerChecker()
{
}

CreatureStatisticsMarkerChecker::CreatureStatisticsMarkerChecker(const uint new_interval)
: minutes_interval(new_interval)
{
}

void CreatureStatisticsMarkerChecker::tick(CreaturePtr creature, TilePtr tile, const ulonglong min_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature != nullptr)
  {
    if (total_minutes_elapsed % minutes_interval == 0)
    {
      check_strength_conditions(creature);
      check_health_conditions(creature);
      check_charisma_conditions(creature);
    }
  }
}

// If a creature is consistently carrying around heavy loads, it will become
// stronger.
void CreatureStatisticsMarkerChecker::check_strength_conditions(CreaturePtr creature)
{
  BurdenLevel bl = BurdenLevelConverter::to_burden_level(creature);
  int num_marks = 0;

  if (bl == BurdenLevel::BURDEN_LEVEL_BURDENED)
  {
    num_marks++;
  }
  else if (bl == BurdenLevel::BURDEN_LEVEL_STRAINED)
  {
    num_marks += 2;
  }

  StatisticsMarker sm;

  if (can_increase_passive_statistic(creature->get_strength()))
  {
    for (int i = 0; i < num_marks; i++)
    {
      sm.mark_strength(creature);
    }
  }
}

// If a creature maintains a good level of satiation, being neither full
// nor hungry, this will increase their overall health.  Up to a point -
// otherwise, Fae would be able to get 99 Hea by just waiting around.
void CreatureStatisticsMarkerChecker::check_health_conditions(CreaturePtr creature)
{
  if (creature != nullptr && can_increase_passive_statistic(creature->get_health()))
  {
    HungerLevel hl = HungerLevelConverter::to_hunger_level(creature->get_hunger_clock().get_hunger());
    RaceManager rm;
    RacePtr race = rm.get_race(creature->get_race_id());
  
    // Ensure that hungerless races like the fae don't easily max out Health 
    // simply by existing.  Hungerless races can still increase health over
    // time, but at a much reduced rate.
    if (race != nullptr)
    {
      HungerCalculator hc;

      if (RNG::percent_chance(hc.calculate_pct_chance_mark_health(hl, race->get_hungerless())))
      {
        StatisticsMarker sm;
        sm.mark_health(creature);
      }
    }
  }
}

void CreatureStatisticsMarkerChecker::check_charisma_conditions(CreaturePtr creature)
{
  Equipment& eq = creature->get_equipment();
  Statistic cha = creature->get_charisma();

  ItemPtr lf = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER);
  ItemPtr rf = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER);
  ItemPtr neck = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  vector<ItemPtr> items = {lf, rf, neck};
  vector<ItemType> jewelry_types = {ItemType::ITEM_TYPE_AMULET, ItemType::ITEM_TYPE_RING};
  bool adorned = false;

  for (ItemPtr item : items)
  {
    if (item != nullptr)
    {
      ItemType itype = item->get_type();

      if (std::find(jewelry_types.begin(), jewelry_types.end(), itype) != jewelry_types.end())
      {
        adorned = true;
        break;
      }
    }
  }

  StatisticsMarker sm;

  if (can_increase_passive_statistic(cha) && adorned)
  {
    sm.mark_charisma(creature);
  }
}

bool CreatureStatisticsMarkerChecker::can_increase_passive_statistic(const Statistic& stat)
{
  bool can_increase = false;
  int modifier = (stat.get_base() - stat.get_original());

  if (modifier < PASSIVE_STATISTIC_THRESHOLD)
  {
    can_increase = true;
  }

  return can_increase;
}