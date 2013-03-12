#pragma once
#include <boost/unordered_map.hpp>
#include "common.hpp"
#include "CalendarTypes.hpp"

typedef boost::unordered_map<Season, int> SeasonTileColourMap;

// A DisplayTile is what the engine says we can see.  This provides a
// separation between the "real" map and the "display" map.  A real map
// tile can have a creature, items, tile info, and so on.  A display map
// tile is much more simple, and only contains what needs to be rendered.
class DisplayTile
{
  public:
    DisplayTile();
    DisplayTile(const uchar symbol, const int colour); // Sets all seasons to the given colour
    DisplayTile(const uchar symbol, const SeasonTileColourMap& new_colours);

    void  set_symbol(const uchar new_symbol);
    uchar get_symbol() const;

    // Set/Get the colour for the season currently set on the tile - stateful.
    void set_colour(const int new_colour);
    int get_colour() const;
    
    // Set/get the current season
    void set_season(const Season new_season);
    Season get_season() const;

    void set_colours(const SeasonTileColourMap& new_colours);
    void set_colour(const Season season, const int new_colour);
    int  get_colour(const Season season) const;
    SeasonTileColourMap get_colours() const;

  protected:
    uchar symbol;
    Season current_season;
    SeasonTileColourMap colours;
};


