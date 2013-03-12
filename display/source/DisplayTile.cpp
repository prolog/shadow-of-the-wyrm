#include "DisplayTile.hpp"

DisplayTile::DisplayTile() : symbol('!'), current_season(SEASON_SPRING)
{
}

DisplayTile::DisplayTile(const uchar sym, const int colour) : symbol(sym), current_season(SEASON_SPRING)
{
  for (int i = SEASON_SPRING; i < SEASON_LAST; i++)
  {
    Season s = static_cast<Season>(i);
    colours[s] = colour;
  }
}

DisplayTile::DisplayTile(const uchar sym, const SeasonTileColourMap& new_map) : symbol(sym), current_season(SEASON_SPRING), colours(new_map)
{
}

void DisplayTile::set_symbol(const uchar sym)
{
  symbol = sym;
}

void DisplayTile::set_colour(const int new_colour)
{
  colours[current_season] = new_colour;
}

int DisplayTile::get_colour() const
{
  return get_colour(current_season);
}

void DisplayTile::set_season(const Season new_season)
{
  current_season = new_season;
}

Season DisplayTile::get_season() const
{
  return current_season;
}

uchar DisplayTile::get_symbol() const
{
  return symbol;
}

void DisplayTile::set_colours(const SeasonTileColourMap& new_colours)
{
  colours = new_colours;
}

void DisplayTile::set_colour(const Season season, const int color)
{
  colours[season] = color;
}

int DisplayTile::get_colour(const Season season) const
{
  int colour = 0;

  SeasonTileColourMap::const_iterator c_it = colours.find(current_season);

  if (c_it != colours.end())
  {
    colour = c_it->second;
  }

  return colour;
}

SeasonTileColourMap DisplayTile::get_colours() const
{
  return colours;
}