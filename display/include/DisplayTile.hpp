#pragma once
#include "common.hpp"

// A DisplayTile is what the engine says we can see.  This provides a
// separation between the "real" map and the "display" map.  A real map
// tile can have a creature, items, tile info, and so on.  A display map
// tile is much more simple, and only contains what needs to be rendered.
class DisplayTile
{
  public:
    DisplayTile();
    DisplayTile(const uchar symbol, const int predefined_colour);

    void  set_symbol(const uchar new_symbol);
    uchar get_symbol() const;

    void set_colour(const int new_colour);
    int  get_colour() const;

  protected:
    uchar symbol;
    int colour;
};


