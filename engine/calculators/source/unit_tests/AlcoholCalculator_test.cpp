#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_AlcoholCalculator, drunk)
{
  AlcoholCalculator ac;
  CreaturePtr creature = CreaturePtr(new Creature());

  Blood b;
  b.set_litres(5.0f);
  b.set_grams_alcohol(5.0f);

  creature->set_blood(b);

  EXPECT_TRUE(ac.is_drunk(creature));

  b.set_grams_alcohol(0.0001f);
  creature->set_blood(b);

  EXPECT_FALSE(ac.is_drunk(creature));
}

TEST(SW_Engine_Calculators_AlcoholCalculator, dead)
{
  AlcoholCalculator ac;

  CreaturePtr creature = CreaturePtr(new Creature());
  Blood b;
  b.set_litres(5.3f);
  b.set_grams_alcohol(2.0f);

  creature->set_blood(b);

  EXPECT_FALSE(ac.is_dead_of_alcohol_poisoning(creature));

  b.set_grams_alcohol(24.9f);

  creature->set_blood(b);

  EXPECT_TRUE(ac.is_dead_of_alcohol_poisoning(creature));
}

