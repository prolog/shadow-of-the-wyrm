#include "gtest/gtest.h"

TEST(SW_World_Religion_DeityStatus, decrement_piety)
{
  DeityStatus ds;

  EXPECT_EQ(100, ds.get_piety());

  ds.increment_piety(100);

  EXPECT_EQ(200, ds.get_piety());

  ds.decrement_piety(200);

  EXPECT_EQ(0, ds.get_piety());

  ds.decrement_piety(9000);

  EXPECT_EQ(-7000, ds.get_piety());

  ds.increment_piety(1000000);

  EXPECT_EQ(25000, ds.get_piety());
}

TEST(SW_World_Religion_DeityStatus, piety_bonus)
{
  DeityStatus ds;

  EXPECT_EQ(0, ds.get_piety_regen_bonus());

  ds.set_piety_regen_bonus(7);

  EXPECT_EQ(7, ds.get_piety_regen_bonus());
}

TEST(SW_World_Religion_DeityStatus, serialization_id)
{
  DeityStatus ds;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DEITY_STATUS, ds.get_class_identifier());
}

TEST(SW_World_Religion_DeityStatus, saveload)
{
  DeityStatus ds1, ds2;

  ds1.set_piety(1234);
  ds1.set_piety_regen_bonus(2);
  ds1.set_champion_type(ChampionType::CHAMPION_TYPE_FALLEN);

  ostringstream ss;

  ds1.serialize(ss);

  istringstream iss(ss.str());

  ds2.deserialize(iss);

  EXPECT_TRUE(ds1 == ds2);
}

TEST(SW_World_Religion_DeityStatus, set_godless)
{
  DeityStatus ds1;

  ds1.set_null(true);
  EXPECT_EQ(0, ds1.get_piety());
  EXPECT_EQ(0, ds1.get_piety_regen_bonus());
  EXPECT_EQ(ChampionType::CHAMPION_TYPE_UNCROWNED, ds1.get_champion_type());
}