#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_Calculator_ItemBreakageCalculator, calculate_pct_chance_digging_breakage)
{
  ItemBreakageCalculator ibc;

  EXPECT_EQ(50, ibc.calculate_pct_chance_digging_breakage(nullptr, nullptr));

  ItemPtr amulet = std::make_shared<Amulet>();
  CreaturePtr creature = std::make_shared<Creature>();
  amulet->set_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_BREAKAGE_PCT_CHANCE, "18");

  EXPECT_EQ(18, ibc.calculate_pct_chance_digging_breakage(creature, amulet));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 50);

  EXPECT_EQ(9, ibc.calculate_pct_chance_digging_breakage(creature, amulet));
}

TEST(SW_Engine_Calculator_ItemBreakageCalculator, calculate_skill_breakage_multiplier)
{
  ItemBreakageCalculator ibc;

  EXPECT_FLOAT_EQ(1.0f, ibc.calculate_skill_breakage_multiplier(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FLOAT_EQ(1.0f, ibc.calculate_skill_breakage_multiplier(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 60);

  EXPECT_FLOAT_EQ(0.40f, ibc.calculate_skill_breakage_multiplier(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 100);

  EXPECT_FLOAT_EQ(0.15f, ibc.calculate_skill_breakage_multiplier(creature));
}

