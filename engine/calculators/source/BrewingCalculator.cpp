#include "BrewingCalculator.hpp"

using namespace std;

const int BrewingCalculator::ADDITIONAL_POTION_BREWING_DIVISOR = 4;
const int BrewingCalculator::STATUS_THRESHOLD_CURSED = 0;
const int BrewingCalculator::STATUS_THRESHOLD_UNCURSED = 40;
const int BrewingCalculator::STATUS_THRESHOLD_BLESSED = 80;

int BrewingCalculator::calc_pct_chance_additional_potion(CreaturePtr creature) const
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    int brewing_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_BREWING);

    if (brewing_val == 100)
    {
      pct_chance = 100;
    }
    else
    {
      pct_chance = brewing_val / ADDITIONAL_POTION_BREWING_DIVISOR;
    }
  }

  return pct_chance;
}

map<ItemStatus, int> BrewingCalculator::calc_item_status_pct_chance(CreaturePtr brewing_creature) const
{
  map<ItemStatus, int> statuses = { {ItemStatus::ITEM_STATUS_CURSED, 100},
                                    {ItemStatus::ITEM_STATUS_UNCURSED, 0},
                                    {ItemStatus::ITEM_STATUS_BLESSED,  0} };

  if (brewing_creature != nullptr)
  {
    int brewing_val = brewing_creature->get_skills().get_value(SkillType::SKILL_GENERAL_BREWING);
    vector<pair<ItemStatus, int>> status_and_threshold = { {ItemStatus::ITEM_STATUS_CURSED, STATUS_THRESHOLD_CURSED}, 
                                                           {ItemStatus::ITEM_STATUS_UNCURSED, STATUS_THRESHOLD_UNCURSED}, 
                                                           {ItemStatus::ITEM_STATUS_BLESSED, STATUS_THRESHOLD_BLESSED} };

    for (const auto& st : status_and_threshold)
    {
      if (brewing_val < st.second)
      {
        statuses[st.first] = brewing_val;
      }
      else
      {
        statuses[st.first] = 100;
      }
    }
  }

  return statuses;
}

#ifdef UNIT_TESTS
#include "unit_tests/BrewingCalculator_test.cpp"
#endif
