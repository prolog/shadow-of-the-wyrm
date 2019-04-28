#include "TileDescriber.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"
#include "TileTextKeys.hpp"

using namespace std;

TileDescriber::TileDescriber(CreaturePtr new_creature, TilePtr new_tile)
: viewing_creature(new_creature), tile(new_tile)
{
}

string TileDescriber::describe() const
{
  string description;

  if (viewing_creature != nullptr && tile != nullptr)
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

    vector<string> extra_sids = tile->get_extra_description_sids();
    if (!extra_sids.empty())
    {
      for (const auto& sid : extra_sids)
      {
        description = description + " " + StringTable::get(sid);
      }
    }

    if (tile->has_engraving())
    {
      description = description + " " + TextMessages::get_engraving_message(tile->get_engraving_sid());
    }

    if (tile->has_inscription())
    {
      CurrentCreatureAbilities cca;
      bool can_read = cca.can_read(viewing_creature);

      if (can_read)
      {
        description = description + " " + TextMessages::get_inscription_message(tile->get_inscription_sid());
      }
      else
      {
        description = description + " " + StringTable::get(TileTextKeys::TILE_INSCRIPTION_ILLITERATE);
      }
    }

    if (tile->get_submerged())
    {
      description = description + " " + StringTable::get(TileTextKeys::TILE_DESC_SUBMERGED);
    }

    Game& game = Game::instance();
    Season season = game.get_current_world()->get_calendar().get_season()->get_season();

    if (tile->get_is_frozen(season))
    {
      description = description + " " + StringTable::get(TileTextKeys::TILE_DESC_FROZEN);
    }
  }

  return description;
}
