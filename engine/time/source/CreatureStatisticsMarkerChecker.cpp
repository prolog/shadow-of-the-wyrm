#include "CreatureStatisticsMarkerChecker.hpp"
#include "Conversion.hpp"
#include "StatisticsMarker.hpp"

using namespace std;

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

  for (int i = 0; i < num_marks; i++)
  {
    sm.mark_strength(creature);
  }
}

// If a creature maintains a good level of satiation, being neither full
// nor hungry, this will increase their overall health.
void CreatureStatisticsMarkerChecker::check_health_conditions(CreaturePtr creature)
{
  HungerLevel hl = HungerLevelConverter::to_hunger_level(creature->get_hunger_clock().get_hunger());

  if (hl == HungerLevel::HUNGER_LEVEL_NORMAL)
  {
    StatisticsMarker sm;
    sm.mark_health(creature);
  }
}

void CreatureStatisticsMarkerChecker::check_charisma_conditions(CreaturePtr creature)
{
  Equipment& eq = creature->get_equipment();
  ItemPtr lf = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER);
  ItemPtr rf = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER);
  ItemPtr neck = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  vector<ItemPtr> items = {lf, rf, neck};
  vector<ItemType> jewelry_types = {ItemType::ITEM_TYPE_AMULET, ItemType::ITEM_TYPE_RING};
  int num_marks = 0;

  for (ItemPtr item : items)
  {
    if (item != nullptr)
    {
      ItemType itype = item->get_type();

      if (std::find(jewelry_types.begin(), jewelry_types.end(), itype) != jewelry_types.end())
      {
        num_marks++;
      }
    }
  }

  StatisticsMarker sm;

  for (int i = 0; i < num_marks; i++)
  {
    sm.mark_charisma(creature);
  }
}