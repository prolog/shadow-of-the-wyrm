#include "DisplayTile.hpp"

DisplayTile::DisplayTile() : current_season(Season::SEASON_SPRING)
{
}

DisplayTile::DisplayTile(const Symbol& new_symbol) 
: symbol(new_symbol), current_season(Season::SEASON_SPRING)
{
  int icolour = static_cast<int>(symbol.get_colour());

  for (int i = static_cast<int>(Season::SEASON_SPRING); i < static_cast<int>(Season::SEASON_LAST); i++)
  {
    Season s = static_cast<Season>(i);
    colours[s] = icolour;
  }
}

DisplayTile::DisplayTile(const Symbol& new_symbol, const SeasonTileColourMap& new_map) 
: symbol(new_symbol), current_season(Season::SEASON_SPRING), colours(new_map)
{
}

void DisplayTile::set_symbol(const Symbol& new_symbol)
{
  symbol = new_symbol;
}

void DisplayTile::set_colour(const int new_colour)
{
  colours[current_season] = new_colour;
}

void DisplayTile::set_all_colours(const int new_colour)
{
  for (auto& c_pair : colours)
  {
    colours[c_pair.first] = new_colour;
  }
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

Symbol DisplayTile::get_symbol() const
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
