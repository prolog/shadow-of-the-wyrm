#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_Calculators_CreateItemCalculator, calc_potential_improvement_points)
{
  CreateItemCalculator cic;
  CreaturePtr creature;

  EXPECT_EQ(0, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER, ItemStatus::ITEM_STATUS_UNCURSED));

  creature = std::make_shared<Creature>();
  Skills& skills = creature->get_skills();

  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 22);

  EXPECT_EQ(1, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER, ItemStatus::ITEM_STATUS_UNCURSED));

  skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 14);

  EXPECT_EQ(3, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER, ItemStatus::ITEM_STATUS_UNCURSED));

  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 60);
  skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 50);

  EXPECT_EQ(12, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER, ItemStatus::ITEM_STATUS_UNCURSED));

  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 100);
  skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 100);

  EXPECT_EQ(22, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER, ItemStatus::ITEM_STATUS_UNCURSED));
  EXPECT_EQ(24, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER, ItemStatus::ITEM_STATUS_BLESSED));
  EXPECT_EQ(20, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER, ItemStatus::ITEM_STATUS_CURSED));
}

TEST(SW_Engine_Calculators_CreateItemCalculator, calc_quantity)
{
  CreateItemCalculator cic;
  ItemPtr creation_item;
  ItemPtr component_item;

  EXPECT_EQ(0, cic.calc_quantity(creation_item, component_item));

  Weight creation_weight(16);
  creation_item = std::make_shared<Amulet>();
  creation_item->set_weight(creation_weight);

  EXPECT_EQ(0, cic.calc_quantity(creation_item, component_item));

  Weight component_weight(16);
  component_item = std::make_shared<Amulet>();
  component_item->set_weight(component_weight);

  EXPECT_EQ(1, cic.calc_quantity(creation_item, component_item));

  component_weight.set_weight(64);
  component_item->set_weight(component_weight);

  EXPECT_EQ(4, cic.calc_quantity(creation_item, component_item));
}
