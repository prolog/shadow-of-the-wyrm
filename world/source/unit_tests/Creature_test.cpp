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
  CreatureSize size = CREATURE_SIZE_LARGE;
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
