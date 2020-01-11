#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_DecorativeStatues, serialization_ids)
{
  Symbol s('?', Colour::COLOUR_WHITE);

  KingDecorativeStatue kds(s);
  QueenDecorativeStatue qds(s);
  WarlordDecorativeStatue wds(s);
  KnightDecorativeStatue knds(s);
  HighPriestDecorativeStatue hpds(s);
  SorcerorDecorativeStatue sds(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE, kds.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE, qds.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE, wds.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE, knds.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE, hpds.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE, sds.get_class_identifier());
}

