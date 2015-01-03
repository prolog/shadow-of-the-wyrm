#include "gtest/gtest.h"

class SL_Engine_Game : public ::testing::Test
{
  protected:
    ClassIdentifier get_class_identifier() { return game.get_class_identifier(); }

    Game game;
};

TEST_F(SL_Engine_Game, serialization_id)
{
  EXPECT_EQ(ClassIdentifier::CLASS_ID_GAME, get_class_identifier());
}

