#include "DisplayTile.hpp"

// FIXME: Create default constants.
DisplayTile::DisplayTile() : symbol('!'), colour(0)
{
}

DisplayTile::DisplayTile(const uchar sym, const int color) : symbol(sym), colour(color)
{
}

void DisplayTile::set_symbol(const uchar sym)
{
  symbol = sym;
}

uchar DisplayTile::get_symbol() const
{
  return symbol;
}

void DisplayTile::set_colour(const int color)
{
  colour = color;
}

int DisplayTile::get_colour() const
{
  return colour;
}

