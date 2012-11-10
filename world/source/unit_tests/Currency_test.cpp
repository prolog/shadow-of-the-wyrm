#include "gtest/gtest.h"

TEST(SL_World_Currency, serialization_id)
{
  Currency currency;

  EXPECT_EQ(CLASS_ID_CURRENCY, currency.get_class_identifier());
}
