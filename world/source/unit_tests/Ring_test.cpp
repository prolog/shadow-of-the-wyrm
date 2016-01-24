#include "gtest/gtest.h"

TEST(SW_World_Ring, serialization_id)
{
  Ring ring;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_RING, ring.get_class_identifier());
}

TEST(SW_World_Ring, saveload)
{
  Ring ring, ring2;

  ring.set_quantity(10);

  ostringstream ss;

  ring.serialize(ss);

  istringstream iss(ss.str());

  ring2.deserialize(iss);

  EXPECT_TRUE(ring == ring2);
}
