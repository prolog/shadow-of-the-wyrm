#include "gtest/gtest.h"
#include "EngineConversion.hpp"
#include "Food.hpp"

TEST(SW_Engine_Calculators_AlcoholCalculator, absorption_rate)
{
  CreaturePtr male = std::make_shared<Creature>();
  male->set_sex(CreatureSex::CREATURE_SEX_MALE);
  male->set_grams_unabsorbed_alcohol(100);

  CreaturePtr female = std::make_shared<Creature>();
  female->set_sex(CreatureSex::CREATURE_SEX_FEMALE);
  female->set_grams_unabsorbed_alcohol(100);

  AlcoholCalculator ac;

  EXPECT_FLOAT_EQ(1.0f, ac.calculate_grams_to_absorb(male));
  EXPECT_FLOAT_EQ(1.5f, ac.calculate_grams_to_absorb(female));

  std::map<int, pair<float, float>> hunger_and_grams = { {HungerLevelConverter::INT_HUNGER_LEVEL_DYING, {2.0f, 3.0f}}, 
                                                         {HungerLevelConverter::INT_HUNGER_LEVEL_STARVING, {2.0f, 3.0f}}, 
                                                         {HungerLevelConverter::INT_HUNGER_LEVEL_HUNGRY, {2.0f, 3.0f}}, {10000, {1.0f, 1.5f}},
                                                         {HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL, {1.0f, 1.5f}},
                                                         {HungerLevelConverter::INT_HUNGER_LEVEL_FULL, {1.0f, 1.5f}},
                                                         {HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED, {1.0f, 1.5f}} };

  for (const auto& hg_pair : hunger_and_grams)
  {
    male->get_hunger_clock_ref().set_hunger(hg_pair.first);
    female->get_hunger_clock_ref().set_hunger(hg_pair.first);

    EXPECT_FLOAT_EQ(hg_pair.second.first, ac.calculate_grams_to_absorb(male));
    EXPECT_FLOAT_EQ(hg_pair.second.second, ac.calculate_grams_to_absorb(female));
  }
}

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

