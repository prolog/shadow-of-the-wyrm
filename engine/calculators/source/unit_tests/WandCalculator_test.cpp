#include "gtest/gtest.h"

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