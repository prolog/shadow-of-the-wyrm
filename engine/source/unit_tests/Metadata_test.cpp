#include "gtest/gtest.h"

TEST(SL_Engine_Metadata, serialization_id)
{
  Metadata m;

  EXPECT_EQ(CLASS_ID_METADATA, m.get_class_identifier());
}
