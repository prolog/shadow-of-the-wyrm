#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Lock, serialization_id)
{
  Lock lock;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_LOCK, lock.get_class_identifier());
}

TEST(SL_World_Tiles_Features_Lock, saveload)
{
  Lock lock, lock2;

  lock.set_locked(false);
  lock.set_lock_id("lock_id!");

  ostringstream oss;

  lock.serialize(oss);

  istringstream iss(oss.str());

  lock2.deserialize(iss);

  EXPECT_TRUE(lock == lock2);
}
