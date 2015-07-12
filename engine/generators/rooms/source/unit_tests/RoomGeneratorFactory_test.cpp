#include "gtest/gtest.h"

TEST(SL_Engine_Generators_Rooms_RoomGeneratorFactory, generator_not_null)
{
  RoomGeneratorFactory rgf;

  for (int i = 0; i < static_cast<int>(RoomType::ROOM_TYPE_LAST); i++)
  {
    RoomType rt = static_cast<RoomType>(i);

    IRoomGeneratorPtr rg = rgf.create_room_generator(rt);

    EXPECT_TRUE(rg != nullptr);
  }
}

