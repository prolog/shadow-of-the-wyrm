#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_EntranceState, serialization_id)
{
  EntranceState es;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ENTRANCE_STATE, es.get_class_identifier());
}


