#include "gtest/gtest.h"
#include "Amulet.hpp"
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

TEST(SW_Engine_Calculators_StatisticsCalculators_Speed, calculate_creature_speed_base)
{
  Statistic speed(47);
  CreaturePtr c = std::make_shared<Creature>();
  c->set_speed(speed);

  SpeedCalculator sc;

  EXPECT_EQ(0, sc.calculate_current(nullptr));

  EXPECT_EQ(47, sc.calculate_current(c));
}

TEST(SW_Engine_Calculators_StatisticsCalculators_Speed, calculate_burdened_and_strained)
{
  Statistic speed(50);
  Statistic str(10);
  CreaturePtr c = std::make_shared<Creature>();
  c->set_speed(speed);
  c->set_strength(str);

  // Add some items to increase weight.
  ItemPtr amulet = std::make_shared<Amulet>();
  Weight weight(16);
  amulet->set_quantity(110);
  amulet->set_weight(weight);

  c->get_inventory()->add_front(amulet);

  SpeedCalculator sc;
  int exp_speed = static_cast<int>(50 * 1.5);
  EXPECT_EQ(exp_speed, sc.calculate_current(c));

  amulet->set_quantity(150);

  exp_speed = static_cast<int>(50 * 2.0);
  EXPECT_EQ(exp_speed, sc.calculate_current(c));

  amulet->set_quantity(2000);

  exp_speed = static_cast<int>(50 * 3.0);
  EXPECT_EQ(exp_speed, sc.calculate_current(c));
}

