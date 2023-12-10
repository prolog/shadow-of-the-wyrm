#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "RockTile.hpp"
#include "EarthTile.hpp"

TEST(SW_Engine_Calculator_ItemBreakageCalculator, calculate_pct_chance_digging_breakage)
{
  ItemBreakageCalculator ibc;
  TilePtr rock_tile = std::make_shared<RockTile>();
  TilePtr earth_tile = std::make_shared<EarthTile>();

  EXPECT_EQ(50, ibc.calculate_pct_chance_digging_breakage(nullptr, nullptr, nullptr));
  EXPECT_EQ(0, ibc.calculate_pct_chance_digging_breakage(nullptr, earth_tile, nullptr));
  EXPECT_EQ(50, ibc.calculate_pct_chance_digging_breakage(nullptr, rock_tile, nullptr));

  ItemPtr amulet = std::make_shared<Amulet>();
  CreaturePtr creature = std::make_shared<Creature>();
  amulet->set_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_BREAKAGE_PCT_CHANCE, "18");

  EXPECT_EQ(18, ibc.calculate_pct_chance_digging_breakage(creature, nullptr, amulet));
  EXPECT_EQ(0, ibc.calculate_pct_chance_digging_breakage(creature, earth_tile, amulet));
  EXPECT_EQ(18, ibc.calculate_pct_chance_digging_breakage(creature, rock_tile, amulet));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 50);

  EXPECT_EQ(9, ibc.calculate_pct_chance_digging_breakage(creature, nullptr, amulet));
  EXPECT_EQ(0, ibc.calculate_pct_chance_digging_breakage(creature, earth_tile, amulet));
  EXPECT_EQ(9, ibc.calculate_pct_chance_digging_breakage(creature, rock_tile, amulet));
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

TEST(SW_Engine_Calculator_ItemBreakageCalculator, get_status_breakage_multiplier)
{
  ItemBreakageCalculator ibc;

  ItemPtr amulet = std::make_shared<Amulet>();
  std::map<ItemStatus, float> mults = { {ItemStatus::ITEM_STATUS_CURSED, 2.0f}, {ItemStatus::ITEM_STATUS_UNCURSED, 1.0f}, {ItemStatus::ITEM_STATUS_BLESSED, 0.5f} };

  for (const auto& m_pair : mults)
  {
    amulet->set_status(m_pair.first);
    EXPECT_FLOAT_EQ(m_pair.second, ibc.get_status_breakage_multiplier(amulet->get_status()));
  }
}