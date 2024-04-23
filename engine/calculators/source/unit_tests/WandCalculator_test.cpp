#include "gtest/gtest.h"
#include "Wand.hpp"

TEST(SW_Engine_Calculator_WandCalculator, explosion_damage)
{
  WandCalculator wc;

  EXPECT_EQ(0, wc.calc_explosion_damage(nullptr));

  WandPtr wand = std::make_shared<Wand>();
  int cur_charges = wand->get_charges().get_current();

  EXPECT_EQ(cur_charges * 3, wc.calc_explosion_damage(wand));

  wand->set_charges(4);

  EXPECT_EQ(12, wc.calc_explosion_damage(wand));
}

TEST(SW_Engine_Calculator_WandCalculator, explode_chance)
{
  CreaturePtr creature = std::make_shared<Creature>();
  WandCalculator wc;
  
  WandPtr wand = std::make_shared<Wand>();

  wand->set_status(ItemStatus::ITEM_STATUS_BLESSED);
  pair<int, int> chance = make_pair(0, 1);

  EXPECT_EQ(chance, wc.calc_x_in_y_chance_explode(creature, wand));
  
  wand->set_status(ItemStatus::ITEM_STATUS_UNCURSED);

  EXPECT_EQ(chance, wc.calc_x_in_y_chance_explode(creature, wand));

  wand->set_status(ItemStatus::ITEM_STATUS_CURSED);
  chance = { 1, 100 };

  EXPECT_EQ(chance, wc.calc_x_in_y_chance_explode(creature, wand));

  vector<pair<int, pair<int, int>>> wc_and_xy = { {1, {1, 104}}, {10, {1, 140}}, {31, {1, 224}}, {50, {1, 300}}, {51, {0, 1}} };

  for (const auto& wc_pair : wc_and_xy)
  {
    creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, wc_pair.first);
    EXPECT_EQ(wc_pair.second, wc.calc_x_in_y_chance_explode(creature, wand));
  }
}

TEST(SW_Engine_Calculators_WandCalculator, damage_bonus)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 33);
  Statistic willpower(18);
  creature->set_willpower(willpower);
  WandCalculator wc;

  EXPECT_EQ(7, wc.calc_damage_bonus(creature));

  Statistic will2(30);
  creature->set_willpower(will2);

  EXPECT_EQ(8, wc.calc_damage_bonus(creature));
}

TEST(SW_Engine_Calculators_WandCalculator, chance_free_charge)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 33);
  WandCalculator wc;

  EXPECT_EQ(3, wc.calc_pct_chance_free_charge(creature));
}

TEST(SW_Engine_Calculators_WandCalculator, spell_castings_per_charge)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 5);
  WandCalculator wc;

  EXPECT_EQ(10, wc.calc_spell_castings_per_charge(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 27);

  EXPECT_EQ(8, wc.calc_spell_castings_per_charge(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 62);

  EXPECT_EQ(4, wc.calc_spell_castings_per_charge(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 80);

  EXPECT_EQ(2, wc.calc_spell_castings_per_charge(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 99);

  EXPECT_EQ(2, wc.calc_spell_castings_per_charge(creature));
}

TEST(SW_Engine_Calculators_WandCalculator, num_charges)
{
  WandCalculator wc;

  EXPECT_EQ(1, wc.calc_num_charges(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_EQ(1, wc.calc_num_charges(nullptr));

  Statistic intl(17);
  creature->set_intelligence(intl);

  EXPECT_EQ(2, wc.calc_num_charges(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 20);

  EXPECT_EQ(3, wc.calc_num_charges(creature));

  Statistic intl2(50);
  creature->set_intelligence(intl2);
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 100);

  EXPECT_EQ(10, wc.calc_num_charges(creature));
}

TEST(SW_Engine_Calculators_WandCalculator, calc_max_recharge_charges)
{
  WandCalculator wc;
  CreaturePtr creature = std::make_shared<Creature>();
  std::vector<std::pair<ItemStatus, int>> status_base_charges = { {ItemStatus::ITEM_STATUS_CURSED, 1}, {ItemStatus::ITEM_STATUS_UNCURSED, 2}, {ItemStatus::ITEM_STATUS_BLESSED, 3} };

  for (const auto& sbase : status_base_charges)
  {
    for (int i = 1; i <= 3; i++)
    {
      int wandcraft_val = i * 33;
      creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, wandcraft_val);
      int exp_val = sbase.second + i;

      EXPECT_EQ(exp_val, wc.calc_max_recharge_charges(creature, sbase.first));
    }
  }
}