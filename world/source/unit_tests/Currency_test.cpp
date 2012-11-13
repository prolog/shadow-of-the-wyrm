#include "gtest/gtest.h"

TEST(SL_World_Currency, serialization_id)
{
  Currency currency;

  EXPECT_EQ(CLASS_ID_CURRENCY, currency.get_class_identifier());
}

TEST(SL_World_Currency, saveload)
{
  Currency currency, currency2;

  currency.set_quantity(5000);

  ostringstream ss;

  currency.serialize(ss);

  istringstream iss(ss.str());

  currency2.deserialize(iss);

  EXPECT_TRUE(currency == currency2);
}
