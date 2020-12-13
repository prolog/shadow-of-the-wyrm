#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_SpellbookCalculator, calculate_pct_chance_wild_incineration)
{
  SpellbookCalculator sc;

  for (uint i = 0; i < 20; i++)
  {
    int exp_value = static_cast<int>(i) * 5;

    if (exp_value > 80)
    {
      exp_value = 80;
    }

    EXPECT_EQ(exp_value, sc.calculate_pct_chance_wild_incineration(i));
  }
}

TEST(SW_Engine_Calculators_SpellbookCalculator, get_ap_amount)
{
  SpellbookCalculator sc;

  CreaturePtr creature = std::make_shared<Creature>();
  Statistic base_ap(30);
  int spell_ap = 15;

  creature->set_arcana_points(base_ap);
  Statistic& ap = creature->get_arcana_points_ref();

  map<int, int> exp_and_actual = { {25, 5}, {20, 10}, {10, 15}, {3, 15} };

  for (const auto& ea_pair : exp_and_actual)
  {
    ap.set_current(ea_pair.first);
    EXPECT_EQ(ea_pair.second, sc.get_ap_amount(spell_ap, creature));
  }
}
