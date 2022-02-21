#include "gtest/gtest.h"
#include "DepthBasedDangerLevelCalculator.hpp"

TEST(SW_World_Calculators_DangerLevelCalculator, set_property)
{
  std::unique_ptr<DangerLevelCalculator> dc = std::make_unique<DepthBasedDangerLevelCalculator>(ExitMovementType::EXIT_MOVEMENT_DESCEND);
  dc->set_property("key", "value");

  EXPECT_EQ("value", dc->get_property("key"));
}

TEST(SW_World_Calculators_DangerLevelCalculator, set_properties)
{
  map<string, string> props = { {"a", "b"}, {"c", "d"} };
  std::unique_ptr<DangerLevelCalculator> dc = std::make_unique<DepthBasedDangerLevelCalculator>(ExitMovementType::EXIT_MOVEMENT_DESCEND);

  dc->set_properties(props);
  EXPECT_EQ(props, dc->get_properties());
}