#include "gtest/gtest.h"

TEST(SW_Sound_SDLSound, serialization_id)
{
  SDLSound ss;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SDL_SOUND, ss.get_class_identifier());
}

