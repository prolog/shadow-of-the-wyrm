#include "gtest/gtest.h"

TEST(SW_Engine_ShimmerColours, pct_chance)
{
  ShimmerColours sc({Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN});
  EXPECT_EQ(ShimmerColours::BASE_PCT_CHANCE_SHIMMER, sc.get_pct_chance_shimmer());

  ShimmerColours sc2({Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN}, 70);
  EXPECT_EQ(70, sc2.get_pct_chance_shimmer());
}

TEST(SW_Engine_ShimmerColours, shimmer_colours)
{
  // Not enough
  ShimmerColours sc({}, 0);

  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_passable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_impassable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_feature_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc.get_shimmer_colour());

  // Too many
  ShimmerColours sc2({Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN, Colour::COLOUR_BOLD_GREEN}, 70);

  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_passable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_impassable_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_feature_colour());
  EXPECT_EQ(Colour::COLOUR_UNDEFINED, sc2.get_shimmer_colour());

  // Just right
  ShimmerColours sc3({Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN}, 70);

  EXPECT_EQ(Colour::COLOUR_BOLD_BLUE, sc3.get_passable_colour());
  EXPECT_EQ(Colour::COLOUR_BLUE, sc3.get_impassable_colour());
  EXPECT_EQ(Colour::COLOUR_BLUE, sc3.get_feature_colour());
  EXPECT_EQ(Colour::COLOUR_CYAN, sc3.get_shimmer_colour());
}

TEST(SW_Engine_ShimmerColours, serialization_id)
{
  ShimmerColours sc;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SHIMMER_COLOURS, sc.get_class_identifier());
}

TEST(SW_Engine_ShimmerColours, saveload)
{
  vector<Colour> colour_conf = {Colour::COLOUR_BOLD_BLUE, Colour::COLOUR_BLUE, Colour::COLOUR_CYAN};
  ShimmerColours sc(colour_conf, 70);

  ostringstream ss;

  sc.serialize(ss);

  istringstream iss(ss.str());

  ShimmerColours sc2;
  sc2.deserialize(iss);

  EXPECT_TRUE(sc == sc2);
  EXPECT_EQ(Colour::COLOUR_BOLD_BLUE, sc2.get_passable_colour());
  EXPECT_EQ(Colour::COLOUR_BLUE, sc2.get_impassable_colour());
  EXPECT_EQ(Colour::COLOUR_BLUE, sc2.get_feature_colour());
  EXPECT_EQ(Colour::COLOUR_CYAN, sc2.get_shimmer_colour());
  EXPECT_EQ(70, sc2.get_pct_chance_shimmer());
  
  vector<Colour> raw_colours_after_ds = sc2.get_raw_colours();

  EXPECT_EQ(static_cast<uint>(3), raw_colours_after_ds.size());
  EXPECT_EQ(colour_conf, raw_colours_after_ds);
}