#include "gtest/gtest.h"

TEST(SW_Display_SDLDisplay, serialization_id)
{
  SDLDisplay sd;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SDL_DISPLAY, sd.get_class_identifier());
}

