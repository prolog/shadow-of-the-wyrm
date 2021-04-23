#include "gtest/gtest.h"
#include "Food.hpp"

TEST(SW_Engine_Calculators_AlcoholCalculator, grams_to_cancel)
{
  AlcoholCalculator ac;
  Weight w(3, 6);

  Food f;
  f.set_weight(w);
  ConsumablePtr cons = std::make_shared<Food>(f);

  EXPECT_FLOAT_EQ(0.0f, ac.calculate_grams_to_cancel(cons));

  cons->set_metabolizes_alcohol(true);
  float exp = static_cast<float>(w.get_weight()) * 0.2f;

  EXPECT_FLOAT_EQ(exp, ac.calculate_grams_to_cancel(cons));
}

TEST(SW_Engine_Calculators_AlcoholCalculator, immediately_sick)
{
  AlcoholCalculator ac;

  CreaturePtr c = std::make_shared<Creature>();
  c->set_health(9);

  EXPECT_FALSE(ac.is_immediately_sick(nullptr, 5));

  map<float, bool> sick_outcomes = { {0.0f, false}, {1.0f, false}, {2.0f, false}, {3.0f, false}, {4.0f, true}, {5.0f, true} };

  for (const auto& so : sick_outcomes)
  {
    EXPECT_EQ(so.second, ac.is_immediately_sick(c, so.first));
  }
}

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

