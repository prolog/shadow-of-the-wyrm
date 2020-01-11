#include "gtest/gtest.h"

TEST(SW_World_Tiles_Feature_Bench, serialization_id)
{
  Symbol s('-', Colour::COLOUR_WHITE);
  Bench bench(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BENCH, bench.get_class_identifier());
}

