#include "TileDescriber.hpp"
#include "StringTable.hpp"

using std::string;

TileDescriber::TileDescriber(TilePtr new_tile)
: tile(new_tile)
{
}

string TileDescriber::describe() const
{
  string description;

  if (tile)
  {
    description = StringTable::get(tile->get_tile_description_sid());

    if (tile->has_extra_description())
    {
      description = description + " " + StringTable::get(tile->get_extra_description_sid());
    }
  }

  return description;
}
