#include "gtest/gtest.h"
#include "Currency.hpp"

TEST(SL_Engine_Calculators_ScoreCalculator, end_boss_component)
{
  Creature c;
  CreaturePtr cp(new Creature(c));

  Mortuary& m = cp->get_mortuary_ref();
  m.add_creature_kill("end_boss");

  ScoreCalculator sc;

  EXPECT_EQ(ScoreConstants::END_BOSS_BONUS, sc.calculate_score(cp));
}

TEST(SL_Engine_Calculators_ScoreCalculator, currency_component)
{
  Creature c;
  CreaturePtr cp(new Creature(c));

  CurrencyPtr currency = std::make_shared<Currency>();
  currency->set_base_id(ItemIdKeys::ITEM_ID_CURRENCY);
  currency->set_quantity(12345);

  Inventory& inv = cp->get_inventory();
  inv.add(currency);

  ScoreCalculator sc;

  EXPECT_EQ(12345, sc.calculate_score(cp));
}

TEST(SL_Engine_Calculators_ScoreCalculator, level_component)
{
  Creature c;
  CreaturePtr cp(new Creature(c));

  Statistic level(36);
  cp->set_level(level);

  ScoreCalculator sc;

  EXPECT_EQ(3600, sc.calculate_score(cp));
}