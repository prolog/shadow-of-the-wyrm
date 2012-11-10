#include "gtest/gtest.h"

TEST(SL_Engine_Actions_ActionCoordinator, serialization_id)
{
  ActionCoordinator ac;

  EXPECT_EQ(CLASS_ID_ACTION_COORDINATOR, ac.get_class_identifier());
}

class SL_Engine_Actions_ActionCoordinatorFixture : public ::testing::Test
{
  protected:
    void SetUp();

    ActionCoordinator ac;
};

void SL_Engine_Actions_ActionCoordinatorFixture::SetUp()
{
  ActionCost ac1;
  ActionCost ac2;

  ac1.set_cost(1);
  ac2.set_cost(10);

  ac.creature_action_order.insert(make_pair(ac1, "monkey"));
  ac.creature_action_order.insert(make_pair(ac2, "bat"));

  ac.current_map_id = "test!";
}

TEST_F(SL_Engine_Actions_ActionCoordinatorFixture, saveload)
{
  ostringstream ss;

  ac.serialize(ss);

  istringstream iss(ss.str());

  ActionCoordinator new_ac;
  new_ac.deserialize(iss);

  EXPECT_TRUE(ac == new_ac);
}

