#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_CarryingCapacityCalculator, calculate_total_items_carrying_capacity)
{
  CarryingCapacityCalculator ccc;
  CreaturePtr null_creature;

  EXPECT_EQ(0, ccc.calculate_carrying_capacity_total_items(null_creature));

  CreaturePtr c = std::make_shared<Creature>();
  c->set_size(CreatureSize::CREATURE_SIZE_TINY);
  Statistic dex(10);
  c->set_dexterity(dex);

  EXPECT_EQ(100, ccc.calculate_carrying_capacity_total_items(c));

  c->set_size(CreatureSize::CREATURE_SIZE_BEHEMOTH);

  EXPECT_EQ(200, ccc.calculate_carrying_capacity_total_items(c));

  Statistic new_dex(15);
  c->set_dexterity(new_dex);

  EXPECT_EQ(300, ccc.calculate_carrying_capacity_total_items(c));
}

