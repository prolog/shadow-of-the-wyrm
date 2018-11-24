#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_SlotMachine, serialization_id)
{
  SlotMachine sm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SLOT_MACHINE, sm.get_class_identifier());
}

TEST(SW_World_Tiles_Features_SlotMachine, saveload)
{
  SlotMachine sm, sm2;

  sm.set_cost(12);
  sm.set_pct_chance_win(30);
  sm.set_payout_multiplier(2.0f);

  ostringstream oss;

  sm.serialize(oss);

  istringstream iss(oss.str());

  sm2.deserialize(iss);

  EXPECT_TRUE(sm == sm2);
  EXPECT_EQ(12, sm2.get_cost());
  EXPECT_EQ(30, sm2.get_pct_chance_win());
  EXPECT_FLOAT_EQ(2.0f, sm2.get_payout_multiplier());
}

