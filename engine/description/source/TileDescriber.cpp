#include "TileDescriber.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"
#include "TileTextKeys.hpp"

using namespace std;

TileDescriber::TileDescriber(CreaturePtr new_creature, TilePtr new_tile, const bool new_is_world_map)
: viewing_creature(new_creature), tile(new_tile), is_world_map(new_is_world_map)
{
}

string TileDescriber::describe() const
{
  string description;

  if (viewing_creature != nullptr && tile != nullptr)
  {
    string tile_desc = StringTable::get(tile->get_tile_description_sid());
    
    if (!tile_desc.empty())
    {
      tile_desc[0] = static_cast<char>(std::toupper(tile_desc[0]));
      tile_desc += ".";
    }

    description = tile_desc;

    if (tile->has_name())
    {
      boost::replace_first(description, "%s1", tile->get_name());
    }

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

    string remains = tile->get_additional_property(TileProperties::TILE_PROPERTY_REMAINS);
    if (!remains.empty() && (String::to_bool(remains) == true))
    {
      description = description + " " + StringTable::get(TileTextKeys::TILE_DESC_REMAINS);
    }

    // Don't use the creature for the check because the tile should always
    // say if it's deathly or not.
    bool deathly = tile->get_unprotected_movement_is_death(nullptr);
    if (deathly)
    {
      description = description + " " + StringTable::get(TileTextKeys::TILE_DESC_DEATHLY);
    }

    vector<string> extra_sids = tile->get_extra_description_sids();
    if (!extra_sids.empty())
    {
      for (const auto& sid : extra_sids)
      {
        description = description + " " + StringTable::get(sid);
      }
    }

    if (MapUtils::has_known_treasure(tile, viewing_creature, false))
    {
      description = description + " " + tile->get_additional_property(TileProperties::TILE_PROPERTY_TREASURE_SOURCE);
    }

    if (MapUtils::has_known_shipwreck(nullptr, tile, viewing_creature, false))
    {
      description = description + " " + tile->get_additional_property(TileProperties::TILE_PROPERTY_UNDERWATER_TREASURE_SOURCE);
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
        description = description + " " + TextMessages::get_inscription_message(tile->get_inscription_sid(), is_world_map);
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
