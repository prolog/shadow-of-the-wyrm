#include "gtest/gtest.h"

TEST(SW_Display_SDL, sdl_color_eq)
{
  SDL sdl;

  SDL_Color black = {0,0,0,255};
  SDL_Color black_alpha2 = {0,0,0, 100};
  SDL_Color black2 = {0,0,0,255};
  SDL_Color blue = {0,0,255,255};

  EXPECT_TRUE(sdl.sdl_color_eq(black, black2));
  EXPECT_FALSE(sdl.sdl_color_eq(black, black_alpha2));
  EXPECT_FALSE(sdl.sdl_color_eq(black, blue));
}

