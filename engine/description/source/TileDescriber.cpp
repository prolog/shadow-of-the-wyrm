#include "TileDescriber.hpp"
#include "Conversion.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"
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

    string planted = tile->get_additional_property(TileProperties::TILE_PROPERTY_PLANTED);
    if (!planted.empty() && (String::to_bool(planted) == true))
    {
      description = description + " " + StringTable::get(TileTextKeys::TILE_DESC_PLANTED);
    }

    if (tile->has_extra_description())
    {
      description = description + " " + StringTable::get(tile->get_extra_description_sid());
    }

    if (tile->has_engraving())
    {
      description = description + " " + TextMessages::get_engraving_message(tile->get_engraving_sid());
    }

    if (tile->has_inscription())
    {
      description = description + " " + TextMessages::get_inscription_message(tile->get_inscription_sid());
    }
  }

  return description;
}
