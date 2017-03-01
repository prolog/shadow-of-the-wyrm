#include "gtest/gtest.h"

TEST(SW_Engine_Time_ShopsTimeObserver, serialization_id)
{
  ShopsTimeObserver so;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SHOPS_TIME_OBSERVER, so.get_class_identifier());
}

