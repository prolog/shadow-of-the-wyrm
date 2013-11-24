#include "DisplayItemColourTranslator.hpp"

using namespace std;

map<ItemStatus, Colour> DisplayItemColourTranslator::status_colours;

DisplayItemColourTranslator::DisplayItemColourTranslator()
{
  if (status_colours.empty()) initialize_status_colours();
}

void DisplayItemColourTranslator::initialize_status_colours()
{
  status_colours.clear();
  status_colours = map<ItemStatus, Colour>{{ITEM_STATUS_BLESSED, COLOUR_BOLD_WHITE},
                                           {ITEM_STATUS_UNCURSED, COLOUR_WHITE},
                                           {ITEM_STATUS_CURSED, COLOUR_BOLD_RED}};
}

Colour DisplayItemColourTranslator::create_colour_for_display_item(ItemPtr item)
{
  Colour colour = COLOUR_WHITE;

  if (item && item->get_status_identified())
  {
    colour = status_colours[item->get_status()];
  }

  return colour;
}

#ifdef UNIT_TESTS
#include "unit_tests/DisplayItemColourTranslator_test.cpp"
#endif