#include "gtest/gtest.h"

TEST(SW_ColourUtils, get_alternate_hue)
{
  std::vector<std::pair<Colour, Colour>> old_new_hue = {{Colour::COLOUR_BLACK, Colour::COLOUR_BOLD_BLACK},
                                                        {Colour::COLOUR_RED, Colour::COLOUR_BOLD_RED},
                                                        {Colour::COLOUR_GREEN, Colour::COLOUR_BOLD_GREEN},
                                                        {Colour::COLOUR_YELLOW, Colour::COLOUR_BOLD_YELLOW},
                                                        {Colour::COLOUR_BLUE, Colour::COLOUR_BOLD_BLUE},
                                                        {Colour::COLOUR_MAGENTA, Colour::COLOUR_BOLD_MAGENTA},
                                                        {Colour::COLOUR_CYAN, Colour::COLOUR_BOLD_CYAN},
                                                        {Colour::COLOUR_WHITE, Colour::COLOUR_BOLD_WHITE}};

  for (const auto& colour_pair : old_new_hue)
  {
    EXPECT_EQ(colour_pair.second, ColourUtils::get_alternate_hue(colour_pair.first));
    EXPECT_EQ(colour_pair.first, ColourUtils::get_alternate_hue(colour_pair.second));
  }
}
