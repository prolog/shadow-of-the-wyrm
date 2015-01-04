#include "gtest/gtest.h"

TEST(SL_World_Creature, name)
{
  Creature c;
  string creature_name = "Bubba Ho Tep";
  c.set_name(creature_name);

  EXPECT_EQ(creature_name, c.get_name());
}

TEST(SL_World_Creature, age)
{
  Creature c;
  int age = 25;
  c.set_age(age);

  EXPECT_EQ(age, c.get_age().get_base());
  EXPECT_EQ(age, c.get_age().get_current());
}

TEST(SL_World_Creature, size)
{
  Creature c;
  CreatureSize size = CreatureSize::CREATURE_SIZE_LARGE;
  c.set_size(size);

  EXPECT_EQ(size, c.get_size());
}

TEST(SL_World_Creature, strength)
{
  Creature c;
  int strength = 12;
  c.set_strength(strength);

  EXPECT_EQ(strength, c.get_strength().get_base());
  EXPECT_EQ(strength, c.get_strength().get_current());
}

TEST(SL_World_Creature, serialization_id)
{
  Creature c;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CREATURE, c.get_class_identifier());
}

TEST(SL_World_Creature, saveload)
{
  Creature c, c2;

  Statistic str(12);
  Statistic dex(11);
  Statistic agi(10);
  Statistic hea(11);
  Statistic intel(12);
  Statistic will(13);
  Statistic cha(14);

  c.set_strength(str);
  c.set_dexterity(dex);
  c.set_agility(agi);
  c.set_health(hea);
  c.set_intelligence(intel);
  c.set_willpower(will);
  c.set_charisma(cha);

  AutomaticMovement& am = c.get_automatic_movement_ref();
  am.set_direction(Direction::DIRECTION_SOUTH);
  am.set_engaged(true);

  Blood b;
  b.set_litres(5.3f);
  b.set_grams_alcohol(1.2f);

  c.set_blood(b);

  ostringstream ss;

  c.serialize(ss);

  istringstream iss(ss.str());

  c2.deserialize(iss);

  EXPECT_TRUE(c == c2);
  EXPECT_FLOAT_EQ(1.2f, c2.get_blood().get_grams_alcohol());
}

