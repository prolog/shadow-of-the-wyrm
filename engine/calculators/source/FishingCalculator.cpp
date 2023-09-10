#include "FishingCalculator.hpp"

using namespace std;

vector<pair<FishingOutcomeType, int>> FishingCalculator::calculate_fishing_outcomes(CreaturePtr creature) const
{
  vector<pair<FishingOutcomeType, int>> outcomes;

  if (creature != nullptr)
  {
    int fishing = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_FISHING);
    ItemPtr item = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

    int pct_catch = std::max(1, (fishing / 2) + get_item_status_outcome_modifier(item));
    int pct_nibble = std::max(0, pct_catch - 4);
    int pct_escape = std::max(0, pct_catch - 9);
    int pct_no_catch = 100; // the default if none of the other outcomes occurs.

    outcomes = {{FishingOutcomeType::FISHING_OUTCOME_CATCH, pct_catch},
               {FishingOutcomeType::FISHING_OUTCOME_NIBBLE, pct_nibble},
               {FishingOutcomeType::FISHING_OUTCOME_ESCAPE, pct_escape},
               {FishingOutcomeType::FISHING_OUTCOME_NO_CATCH, pct_no_catch}};
  }

  return outcomes;
}

int FishingCalculator::get_item_status_outcome_modifier(ItemPtr item) const
{
  int modifier = 0;

  if (item != nullptr)
  {
    switch (item->get_status())
    {
      case ItemStatus::ITEM_STATUS_BLESSED:
        modifier = 10;
        break;
      case ItemStatus::ITEM_STATUS_CURSED:
        modifier = -10;
        break;
      case ItemStatus::ITEM_STATUS_UNCURSED:
      default:
        break;
    }
  }

  return modifier;
}

#ifdef UNIT_TESTS
#include "unit_tests/FishingCalculator_test.cpp"
#endif
