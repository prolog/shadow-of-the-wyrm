#include "gtest/gtest.h"
#include "ParalysisStatusEffect.hpp"

TEST(SW_Engine_Calculators_CombatEffectsCalculator, pct_chance_counter_strike)
{
  CreaturePtr creature = std::make_shared<Creature>();
  CombatEffectsCalculator cec;
  Statistic hp(50);
  creature->set_hit_points(hp);

  EXPECT_EQ(0, cec.calc_pct_chance_counter_strike(nullptr));
  EXPECT_EQ(0, cec.calc_pct_chance_counter_strike(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_COMBAT, 20);
  
  EXPECT_EQ(2, cec.calc_pct_chance_counter_strike(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_COMBAT, 60);

  EXPECT_EQ(6, cec.calc_pct_chance_counter_strike(creature));

  creature->get_dexterity_ref().set_base_current(32);

  EXPECT_EQ(12, cec.calc_pct_chance_counter_strike(creature));

  // Ensure that paralyzed creatures can't counter.
  ParalysisStatusEffect pse;
  pse.apply_change(creature, 50);

  EXPECT_EQ(0, cec.calc_pct_chance_counter_strike(creature));

  pse.undo_change(creature);

  hp.set_current(-2);
  creature->set_hit_points(hp);

  EXPECT_EQ(0, cec.calc_pct_chance_counter_strike(creature));
}

TEST(SW_Engine_Calculators_CombatEffectsCalculator, calculate_knock_back_pct_chance_kick)
{
  CreaturePtr creature;
  CombatEffectsCalculator cec;

  EXPECT_EQ(0, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, creature, nullptr));

  creature = CreaturePtr(new Creature());
  Statistic str(1);
  creature->set_strength(str);

  EXPECT_EQ(0, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, creature, nullptr));

  str.set_base_current(2);
  creature->set_strength(str);

  EXPECT_EQ(0, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, creature, nullptr));

  str.set_base_current(12);
  creature->set_strength(str);

  EXPECT_EQ(4, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, creature, nullptr));

  str.set_base_current(99);
  creature->set_strength(str);

  EXPECT_EQ(33, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, creature, nullptr));
}

TEST(SW_Engine_Calculators_CombatEffectsCalculator, calculate_knock_back_pct_chance_magic)
{
  CreaturePtr creature;
  CreaturePtr creature2;
  CombatEffectsCalculator cec;

  EXPECT_EQ(0, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MAGICAL, creature, nullptr));

  creature = CreaturePtr(new Creature());
  creature2 = CreaturePtr(new Creature());

  Statistic str(30);
  creature->set_strength(str);
  creature2->set_strength(str);

  EXPECT_EQ(0, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MAGICAL, creature, creature2));
}

TEST(SW_Engine_Calculators_CombatEffectsCalculator, calculate_knock_back_pct_chance_primary_mastery)
{
  CreaturePtr creature;
  CreaturePtr creature2;
  CombatEffectsCalculator cec;

  creature = CreaturePtr(new Creature());
  creature2 = CreaturePtr(new Creature());
  creature->get_skills().set_value(SkillType::SKILL_MELEE_UNARMED, Skills::MAX_SKILL_VALUE);

  std::vector<int> str_values = { 8, 12, 23, 40, 86 };
  std::vector<CreatureSize> sizes = { CreatureSize::CREATURE_SIZE_TINY, CreatureSize::CREATURE_SIZE_SMALL, CreatureSize::CREATURE_SIZE_MEDIUM, CreatureSize::CREATURE_SIZE_LARGE, CreatureSize::CREATURE_SIZE_HUGE, CreatureSize::CREATURE_SIZE_BEHEMOTH };

  for (int str : str_values)
  {
    creature->set_strength(str);

    for (const CreatureSize c1_size : sizes)
    {
      creature->set_size(c1_size);

      for (const CreatureSize c2_size : sizes)
      {
        creature2->set_size(c2_size);
        int diff = static_cast<int>(c1_size) - static_cast<int>(c2_size);
        int exp_val = 0;

        
        if (diff < 2)
        {
          exp_val = str / 3;
        }
        else
        {
          exp_val = 100 + (str / 3);
        }

        EXPECT_EQ(exp_val, cec.calculate_knock_back_pct_chance(AttackType::ATTACK_TYPE_MELEE_PRIMARY, creature, creature2));
      }
    }
  }
}

TEST(SW_Engine_Calculators_CombatEffectsCalculator, calculate_knock_back_pct_chance_physical_not_tertiary)
{
  CreaturePtr creature;
  CreaturePtr creature2;
  CombatEffectsCalculator cec;

  creature = CreaturePtr(new Creature());
  creature2 = CreaturePtr(new Creature());

  std::vector<AttackType> attack_types = { AttackType::ATTACK_TYPE_MELEE_PRIMARY, AttackType::ATTACK_TYPE_MELEE_SECONDARY };
  std::vector<int> str_values = { 8, 12, 23, 40, 86 };
  std::vector<CreatureSize> sizes = { CreatureSize::CREATURE_SIZE_TINY, CreatureSize::CREATURE_SIZE_SMALL, CreatureSize::CREATURE_SIZE_MEDIUM, CreatureSize::CREATURE_SIZE_LARGE, CreatureSize::CREATURE_SIZE_HUGE, CreatureSize::CREATURE_SIZE_BEHEMOTH };

  for (AttackType at : attack_types)
  {
    for (int str : str_values)
    {
      creature->set_strength(str);

      for (const CreatureSize c1_size : sizes)
      {
        creature->set_size(c1_size);

        for (const CreatureSize c2_size : sizes)
        {
          creature2->set_size(c2_size);
          int diff = static_cast<int>(c1_size) - static_cast<int>(c2_size);
          int exp_val = 0;

          if (diff >= 2)
          {
            exp_val = str / 3;
          }

          EXPECT_EQ(exp_val, cec.calculate_knock_back_pct_chance(at, creature, creature2));
        }
      }
    }
  }
}
