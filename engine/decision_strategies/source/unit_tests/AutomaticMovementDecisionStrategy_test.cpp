#include "gtest/gtest.h"
#include "AutomaticMovement.hpp"

TEST(SL_Engine_DecisionStrategy_AutomaticMovementDecisionStrategy, serialization_id)
{
  ControllerPtr nullp;
  AutomaticMovement am;
  AutomaticMovementDecisionStrategy ds(am, nullp);

  EXPECT_EQ(CLASS_ID_AUTOMATIC_MOVEMENT_DECISION_STRATEGY, ds.get_class_identifier());
}

TEST(SL_Engine_DecisionStrategy_AutomaticMovementDecisionStrategy, saveload)
{
  AutomaticMovement am;
  ControllerPtr nullp;

  am.set_direction(DIRECTION_NORTH);

  AutomaticMovementDecisionStrategy ds(am, nullp);

  am.set_direction(DIRECTION_SOUTH);

  AutomaticMovementDecisionStrategy ds2(am, nullp);

  ostringstream oss;

  ds.serialize(oss);

  istringstream iss(oss.str());

  ds2.deserialize(iss);

  EXPECT_TRUE(ds == ds2);
}

