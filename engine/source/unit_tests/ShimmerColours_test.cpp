#include "gtest/gtest.h"

TEST(SW_Engine_ShimmerColours, pct_chance)
{
  ShimmerColours sc({Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN});
  EXPECT_EQ(10, sc.get_pct_chance_shimmer());
}

TEST(SW_Engine_ShimmerColours, shimmer_colours)
{
  // Not enough
  ShimmerColours sc({});

  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_passable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_impassable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_feature_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_shimmer_colour());

  // Too many
  ShimmerColours sc2({Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN, Colour::COLOUR_BOLD_GREEN});

  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_passable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_impassable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_feature_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_shimmer_colour());

  // Just right
  ShimmerColours sc3({Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN});

  EXPECT_EQ(Colour::COLOUR_BOLD_BLUE, sc3.get_passable_colour());
  EXPECT_EQ(Colour::COLOUR_BLUE, sc3.get_impassable_colour());
  EXPECT_EQ(Colour::COLOUR_BLUE, sc3.get_feature_colour());
  EXPECT_EQ(Colour::COLOUR_CYAN, sc3.get_shimmer_colour());
}

