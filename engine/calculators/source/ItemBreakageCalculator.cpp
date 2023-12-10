#include "ItemBreakageCalculator.hpp"
#include "Conversion.hpp"
#include "ItemProperties.hpp"

using namespace std;

const int ItemBreakageCalculator::BASE_PCT_CHANCE_DIGGING_BREAKAGE = 50;
const float ItemBreakageCalculator::MIN_SKILL_BREAKAGE_MULTIPLIER = 0.15f;

int ItemBreakageCalculator::calculate_pct_chance_digging_breakage(CreaturePtr creature, TilePtr tile, ItemPtr item) const
{
  int result = BASE_PCT_CHANCE_DIGGING_BREAKAGE;
  float item_status_mult = 1.0f;

  if (item != nullptr)
  {
    string breakage_pct_chance = item->get_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_BREAKAGE_PCT_CHANCE);

    if (!breakage_pct_chance.empty())
    {
      result = String::to_int(breakage_pct_chance);
    }

    item_status_mult = get_status_breakage_multiplier(item->get_status());
  }

  pair<bool, int> override = get_override_pct_chance_breakage(item);

  if (override.first == true)
  {
    result = override.second;
  }

  float skill_break_mult = calculate_skill_breakage_multiplier(creature);
  float tile_break_mult  = calculate_tile_breakage_multiplier(tile);
  
  result = static_cast<int>(result * skill_break_mult * tile_break_mult * item_status_mult);

  return result;
}

pair<bool, int> ItemBreakageCalculator::get_override_pct_chance_breakage(ItemPtr item) const
{
  pair<bool, int> result = make_pair(false, 0);

  if (item != nullptr)
  {
    if (item->get_artifact())
    {
      // Artifacts can't be broken!
      result = make_pair(true, 0);
    }
  }

  return result;
}

float ItemBreakageCalculator::calculate_skill_breakage_multiplier(CreaturePtr creature) const
{
  float skill_mult = 1.0f;

  if (creature != nullptr)
  {
    // Subtract 0.01 for every point of Dungeoneering.
    int dungeoneering_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_DUNGEONEERING);
    skill_mult -= (0.01f * dungeoneering_val);

    // The lowest possible skill multiplier is 0.15
    skill_mult = std::max(skill_mult, MIN_SKILL_BREAKAGE_MULTIPLIER);
  }

  return skill_mult;
}

float ItemBreakageCalculator::calculate_tile_breakage_multiplier(TilePtr tile) const
{
  float tile_mult = 1.0f;

  if (tile != nullptr)
  {
    tile_mult = tile->get_breakage_multiplier();
  }

  return tile_mult;
}

float ItemBreakageCalculator::get_status_breakage_multiplier(const ItemStatus item_status) const
{
  switch (item_status)
  {
    case ItemStatus::ITEM_STATUS_CURSED:
      return 2.0f;
    case ItemStatus::ITEM_STATUS_UNCURSED:
      return 1.0f;
    case ItemStatus::ITEM_STATUS_BLESSED:
    default:
      return 0.5f;
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemBreakageCalculator_test.cpp"
#endif
