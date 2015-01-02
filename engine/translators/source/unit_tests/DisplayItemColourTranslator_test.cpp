#include "gtest/gtest.h"
#include "Wand.hpp"

TEST(SL_Engine_Translators_DisplayItemColourTranslator, correct_colour)
{
  DisplayItemColourTranslator dict;
  ItemPtr wand = ItemPtr(new Wand());

  wand->set_status_identified(false);

  EXPECT_EQ(Colour::COLOUR_WHITE, dict.create_colour_for_display_item(wand));
  
  wand->set_status_identified(true);
  wand->set_status(ItemStatus::ITEM_STATUS_UNCURSED);

  EXPECT_EQ(Colour::COLOUR_WHITE, dict.create_colour_for_display_item(wand));
  
  wand->set_status(ItemStatus::ITEM_STATUS_CURSED);
  EXPECT_EQ(Colour::COLOUR_BOLD_RED, dict.create_colour_for_display_item(wand));

  wand->set_status(ItemStatus::ITEM_STATUS_BLESSED);
  EXPECT_EQ(Colour::COLOUR_BOLD_WHITE, dict.create_colour_for_display_item(wand));
}

