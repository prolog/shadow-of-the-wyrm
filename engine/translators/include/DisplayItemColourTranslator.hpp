#pragma once
#include "Item.hpp"

// This class determines what colour an item should use in the UI, based on
// whether it has been identified, and if so, by its item status.
class DisplayItemColourTranslator
{
  public:
    DisplayItemColourTranslator();

    Colour create_colour_for_display_item(ItemPtr item);

  protected:
    void initialize_status_colours();

    static std::map<ItemStatus, Colour> status_colours;
};

