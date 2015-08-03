#include "TileDescriber.hpp"
#include "Conversion.hpp"
#include "StringTable.hpp"
#include "TileTextKeys.hpp"

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

    string prev_dug = tile->get_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG);
    if (!prev_dug.empty() && (String::to_bool(prev_dug) == true))
    {
      description = description + " " + StringTable::get(TileTextKeys::TILE_DESC_DUG);
    }

    if (tile->has_extra_description())
    {
      description = description + " " + StringTable::get(tile->get_extra_description_sid());
    }
  }

  return description;
}
