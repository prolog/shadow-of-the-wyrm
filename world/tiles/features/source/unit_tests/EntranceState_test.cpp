#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_EntranceState, serialization_id)
{
  EntranceState es;

  EXPECT_EQ(CLASS_ID_ENTRANCE_STATE, es.get_class_identifier());
}


