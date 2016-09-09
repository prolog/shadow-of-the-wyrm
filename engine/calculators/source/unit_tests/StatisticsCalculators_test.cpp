#include "gtest/gtest.h"
#include "ModifyStatisticsEffect.hpp"

CreaturePtr create_test_creature();
CreaturePtr create_test_creature()
{
  CreaturePtr creature = std::make_shared<Creature>();

  Statistic str(15);
  Statistic dex(14);
  Statistic agi(13);
  Statistic hea(12);
  Statistic itl(11);
  Statistic wil(10);
  Statistic cha(16);

  creature->set_strength(str);
  creature->set_dexterity(dex);
  creature->set_agility(agi);
  creature->set_health(hea);
  creature->set_intelligence(itl);
  creature->set_willpower(wil);
  creature->set_charisma(cha);

  Modifier m(vector<int>({ 6, 5, 4, 3, 2, 1, 4 }));

  ModifyStatisticsEffect mse;
  mse.apply_modifiers(creature, m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_PRESET, -1);

  return creature;
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Strength, calculate_current)
{
  CreaturePtr creature = create_test_creature();
  
  StrengthCalculator sc;
  EXPECT_EQ(21, sc.calculate_current(creature));
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Dexterity, calculate_current)
{
  CreaturePtr creature = create_test_creature();

  DexterityCalculator dc;
  EXPECT_EQ(19, dc.calculate_current(creature));
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Agility, calculate_current)
{
  CreaturePtr creature = create_test_creature();

  AgilityCalculator ac;
  EXPECT_EQ(17, ac.calculate_current(creature));
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Health, calculate_current)
{
  CreaturePtr creature = create_test_creature();

  HealthCalculator hc;
  EXPECT_EQ(15, hc.calculate_current(creature));
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Intelligence, calculate_current)
{
  CreaturePtr creature = create_test_creature();

  IntelligenceCalculator ic;
  EXPECT_EQ(13, ic.calculate_current(creature));
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Willpower, calculate_current)
{
  CreaturePtr creature = create_test_creature();

  WillpowerCalculator wc;
  EXPECT_EQ(11, wc.calculate_current(creature));
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Charisma, calculate_current)
{
  CreaturePtr creature = create_test_creature();

  CharismaCalculator cc;
  EXPECT_EQ(20, cc.calculate_current(creature));
}


