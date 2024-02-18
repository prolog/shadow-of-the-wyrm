#include "gtest/gtest.h"

TEST(SW_Sound_NullSound, serialization_id)
{
  NullSound ns;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_NULL_SOUND, ns.get_class_identifier());
}

