#include "gtest/gtest.h"

TEST(SW_Engine_Actions_ActionCostConstants, defaults)
{
  EXPECT_EQ(1, ActionCostConstants::DEFAULT);
  EXPECT_EQ(0, ActionCostConstants::NO_ACTION);
  EXPECT_EQ(-1, ActionCostConstants::NO_ACTION_MENU);
}

TEST(SW_Engine_Actions_ActionCost, serialization_id)
{
  ActionCost ac;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ACTION_COST, ac.get_class_identifier());
}

class SW_Engine_Actions_ActionCostFixture : public ::testing::Test
{
  protected:
    void SetUp();

    ActionCost ac;
};

void SW_Engine_Actions_ActionCostFixture::SetUp()
{
  ac.set_cost(12);
}

TEST_F(SW_Engine_Actions_ActionCostFixture, saveload)
{
  ostringstream ss;

  ac.serialize(ss);

  istringstream iss(ss.str());

  ActionCost ac2;

  ac2.deserialize(iss);

  EXPECT_TRUE(ac == ac2);

}
