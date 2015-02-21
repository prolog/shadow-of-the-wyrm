#include "gtest/gtest.h"

TEST(SL_World_Modifier, is_negative_stats)
{
  Modifier m;

  EXPECT_FALSE(m.is_negative());

  m.set_soak_modifier(-10);

  EXPECT_TRUE(m.is_negative());

  m.set_strength_modifier(5);

  EXPECT_TRUE(m.is_negative());

  m.set_agility_modifier(5);

  EXPECT_FALSE(m.is_negative());
}

TEST(SL_World_Modifier, is_negative_resists)
{
  Modifier m2;

  Resistances r;
  r.set_all_resistances_to(0);
  r.set_resistance_value(DamageType::DAMAGE_TYPE_SLASH, 0.10);
  r.set_resistance_value(DamageType::DAMAGE_TYPE_POUND, -0.05);
  
  m2.set_resistances(r);

  EXPECT_FALSE(m2.is_negative());

  r.set_resistance_value(DamageType::DAMAGE_TYPE_COLD, -0.25);
  m2.set_resistances(r);

  EXPECT_TRUE(m2.is_negative());
}

TEST(SL_World_Modifier, is_negative_both)
{
  Modifier m3;
  Resistances r;
  r.set_all_resistances_to(1);

  m3.set_agility_modifier(-10);

  m3.set_resistances(r);

  EXPECT_TRUE(m3.is_negative());

  m3.set_agility_modifier(5);
  m3.set_resistances(r);

  EXPECT_FALSE(m3.is_negative());

  r.set_all_resistances_to(-0.01);
  m3.set_resistances(r);

  EXPECT_TRUE(m3.is_negative());
}

TEST(SL_World_Modifier, statuses)
{
  Modifier m;
  
  m.set_status("fdsa", true);
  m.set_status("asdf", false);

  EXPECT_EQ(true, m.get_status("fdsa"));
  EXPECT_EQ(true, m.has_status("fdsa"));

  EXPECT_EQ(false, m.get_status("asdf"));
  EXPECT_EQ(true, m.has_status("asdf"));

  EXPECT_EQ(false, m.get_status("abab"));
  EXPECT_EQ(false, m.has_status("abab"));
}

TEST(SL_World_Modifier, get_affected_statuses)
{
  Modifier m;

  vector<string> statuses = { "bad_teeth", "low_self_esteem", "rabies" };
  
  for (const auto& status : statuses)
  {
    m.set_status(status, true);
  }

  m.set_status("talks_out_loud_all_day_while_I_try_to_work", false);
  m.set_status("slurps_coffee_and_then_burps_constantly", false);

  EXPECT_EQ(statuses, m.get_affected_status_keys());
}

TEST(SL_World_Modifier, serialization_id)
{
  Modifier m;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MODIFIER, m.get_class_identifier());
}

TEST(SL_World_Modifier, export_raw)
{
  vector<int> raw_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  Modifier m(raw_values);
  EXPECT_EQ(raw_values, m.get_raw_values());
}

TEST(SL_World_Modifier, saveload)
{
  Modifier m(1,2,3,4,5,6,7);
  m.set_evade_modifier(3);
  m.set_soak_modifier(4);
  m.set_to_hit_modifier(-12);

  m.set_status("asdf", true);

  Modifier m2;

  EXPECT_FALSE(m == m2);

  ostringstream ss;

  m.serialize(ss);

  istringstream iss(ss.str());

  m2.deserialize(iss);

  EXPECT_TRUE(m == m2);
}
