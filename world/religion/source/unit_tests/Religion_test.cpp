#include "gtest/gtest.h"

TEST(SL_World_Religion_Religion, serialization_id)
{
  Religion r;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_RELIGION, r.get_class_identifier());
}

TEST(SL_World_Religion_Religion, saveload)
{
  Religion r, r2;
  DeityStatus d;
  d.set_piety(3456);

  r.set_deity_status("Bob", d);
  r.set_active_deity_id("Bob"); // Fnord

  ostringstream ss;

  r.serialize(ss);

  istringstream iss(ss.str());

  r2.deserialize(iss);

  EXPECT_TRUE(r == r2);
}
