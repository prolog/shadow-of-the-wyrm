#pragma once
#include <unordered_map>
#include <vector>
#include "common.hpp"
#include "CalendarTypes.hpp"
#include "Symbol.hpp"

using SeasonTileColourMap = std::unordered_map<Season, int>;

// A DisplayTile is what the engine says we can see.  This provides a
// separation between the "real" map and the "display" map.  A real map
// tile can have a creature, items, tile info, and so on.  A display map
// tile is much more simple, and only contains what needs to be rendered.
class DisplayTile
{
  public:
    DisplayTile();
    DisplayTile(const Symbol& new_symbol); // Sets all seasons to the given colour
    DisplayTile(const Symbol& new_symbol, const SeasonTileColourMap& new_colours);
    virtual ~DisplayTile() = default;

    void  set_symbol(const Symbol& new_symbol);
    Symbol get_symbol() const;

    // Set/Get the colour for the season currently set on the tile - stateful.
    void set_colour(const int new_colour);
    int get_colour() const;
    
    // Set/get the current season
    void set_season(const Season new_season);
    Season get_season() const;

    void set_colours(const SeasonTileColourMap& new_colours);
    void set_all_colours(const int new_colour);
    void set_colour(const Season season, const int new_colour);
    int  get_colour(const Season season) const;
    SeasonTileColourMap get_colours() const;

    void set_weather_colours(const std::vector<Colour>& new_weather_colours);
    std::vector<Colour> get_weather_colours() const;

  protected:
    Symbol symbol;
    Season current_season;
    SeasonTileColourMap colours;
    std::vector<Colour> weather_colours;
};


