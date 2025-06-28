#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_CarryingCapacityCalculator, calculate_total_items_carrying_capacity)
{
  CarryingCapacityCalculator ccc;
  CreaturePtr null_creature;

  EXPECT_EQ(static_cast<uint>(0), ccc.calculate_carrying_capacity_total_items(null_creature));

  CreaturePtr c = std::make_shared<Creature>();
  c->set_size(CreatureSize::CREATURE_SIZE_TINY);
  Statistic dex(10);
  c->set_dexterity(dex);

  EXPECT_EQ(static_cast<uint>(100), ccc.calculate_carrying_capacity_total_items(c));

  c->set_size(CreatureSize::CREATURE_SIZE_BEHEMOTH);

  EXPECT_EQ(static_cast<uint>(200), ccc.calculate_carrying_capacity_total_items(c));

  Statistic new_dex(15);
  c->set_dexterity(new_dex);

  EXPECT_EQ(static_cast<uint>(300), ccc.calculate_carrying_capacity_total_items(c));

  // Check carrying skill multiplier.
  c->get_skills().set_value(SkillType::SKILL_GENERAL_CARRYING, 50);
  EXPECT_EQ(static_cast<uint>(450), ccc.calculate_carrying_capacity_total_items(c));
}

TEST(SW_Engine_Calculators_CarryingCapacityCalculator, calculate_burdened)
{
  CarryingCapacityCalculator ccc;
  CreaturePtr c = std::make_shared<Creature>();
  Statistic str(10);
  c->set_strength(str);

  EXPECT_EQ(static_cast<uint>(1600), ccc.calculate_burdened_weight(c));

  Statistic str2(15);
  c->set_strength(str2);

  EXPECT_EQ(static_cast<uint>(2400), ccc.calculate_burdened_weight(c));

  c->get_skills().set_value(SkillType::SKILL_GENERAL_CARRYING, 50);
  EXPECT_EQ(static_cast<uint>(4800), ccc.calculate_burdened_weight(c));
}

TEST(SW_Engine_Calculators_CarryingCapacityCalculator, calculate_strained)
{
  CarryingCapacityCalculator ccc;
  CreaturePtr c = std::make_shared<Creature>();
  Statistic str(10);
  c->set_strength(str);

  EXPECT_EQ(static_cast<uint>(2400), ccc.calculate_strained_weight(c));

  Statistic str2(15);
  c->set_strength(str2);

  EXPECT_EQ(static_cast<uint>(3600), ccc.calculate_strained_weight(c));

  c->get_skills().set_value(SkillType::SKILL_GENERAL_CARRYING, 50);
  EXPECT_EQ(static_cast<uint>(7200), ccc.calculate_strained_weight(c));
}

TEST(SW_Engine_Calculators_CarryingCapacityCalculator, calculate_overburdened)
{
  CarryingCapacityCalculator ccc;
  CreaturePtr c = std::make_shared<Creature>();
  Statistic str(10);
  c->set_strength(str);

  EXPECT_EQ(static_cast<uint>(3200), ccc.calculate_overburdened_weight(c));

  Statistic str2(15);
  c->set_strength(str2);

  EXPECT_EQ(static_cast<uint>(4800), ccc.calculate_overburdened_weight(c));

  c->get_skills().set_value(SkillType::SKILL_GENERAL_CARRYING, 50);
  EXPECT_EQ(static_cast<uint>(9600), ccc.calculate_overburdened_weight(c));
}