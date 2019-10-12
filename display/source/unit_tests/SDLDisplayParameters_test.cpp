#include "gtest/gtest.h"

TEST(SW_Display_SDLDisplayParameters, serialization_id)
{
  SDLDisplayParameters sdld;
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SDL_DISPLAY_PARAMETERS, sdld.get_class_identifier());
}

TEST(SW_Display_SDLDisplayParameters, saveload)
{
  SDLDisplayParameters sdld(80, 25, 640, 400, 8, 16, 10, 100);
  SDLDisplayParameters sdld2;

  ostringstream ss;
  sdld.serialize(ss);

  istringstream iss(ss.str());
  sdld2.deserialize(iss);

  EXPECT_EQ(80, sdld2.get_screen_cols());
  EXPECT_EQ(25, sdld2.get_screen_rows());
  EXPECT_EQ(640, sdld2.get_screen_width());
  EXPECT_EQ(400, sdld2.get_screen_height());
  EXPECT_EQ(8, sdld2.get_glyph_width());
  EXPECT_EQ(16, sdld2.get_glyph_height());
  EXPECT_EQ(10, sdld2.get_glyphs_per_line());
  EXPECT_EQ(100, sdld2.get_num_glyphs());

  EXPECT_TRUE(sdld == sdld2);
}
