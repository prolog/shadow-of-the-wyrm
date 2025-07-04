#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include "Conversion.hpp"
#include "Creature.hpp"
#include "CreatureProperties.hpp"
#include "EffectProperties.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SoundEffectID.hpp"
#include "TeleportEffect.hpp"

using namespace std;

const string TeleportEffect::TELEPORT_BLINK = "TELEPORT_BLINK";

TeleportEffect::TeleportEffect()
: blink_effect(false), teleport_location({false, {-1,-1}})
{
}

string TeleportEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
    effect_msg = EffectTextKeys::get_teleport_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

bool TeleportEffect::is_negative_effect() const
{
  return true;
}

Effect* TeleportEffect::clone()
{
  return new TeleportEffect(*this);
}

bool TeleportEffect::effect_blessed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return teleport(creature);
}

bool TeleportEffect::effect_uncursed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return teleport(creature);
}

bool TeleportEffect::effect_cursed(CreaturePtr creature, ActionManager * /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return teleport(creature);
}

bool TeleportEffect::teleport(CreaturePtr creature)
{
  bool teleported = false;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    // The creature's original tile.
    TilePtr old_tile = map->at(map->get_location(creature->get_id()));

    string map_cannot_teleport = map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_TELEPORT);

    if (map_cannot_teleport.empty() || (String::to_bool(map_cannot_teleport) == false))
    {
      if (blink_effect)
      {
        // Blink just teleports in the field of view.
        teleported = blink(creature, map, old_tile);
      }
      else
      {
        // Proper teleporting can go anywhere on the map.
        teleported = teleport(creature, map, old_tile);
      }

      if (teleported)
      {
        Game::instance().get_sound()->play(SoundEffectID::TELEPORT);
      }
    }
    else
    {
      if (creature->get_is_player())
      {
        IMessageManager& manager = MMF::instance();
        manager.add_new_message(StringTable::get(EffectTextKeys::EFFECT_TELEPORT_CANNOT_TELEPORT));
        manager.send();
      }
    }
  }

  if (teleported && creature != nullptr)
  {
    creature->get_automatic_movement_ref().reset();
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_TELEPORTED, std::to_string(true));
  }

  return teleported;
}

void TeleportEffect::read_properties(const map<string, string>& properties)
{
  auto p_it = properties.find(TELEPORT_BLINK);

  if (p_it != properties.end())
  {
    try
    {
      blink_effect = String::to_bool(p_it->second);
    }
    catch (...)
    {
      Log::instance().error("Could not convert blink effect value!");
    }
  }

  p_it = properties.find(EffectProperties::EFFECT_PROPERTIES_TELEPORT_LOCATION);

  if (p_it != properties.end())
  {
    vector<string> coords = String::create_string_vector_from_csv_string(p_it->second);

    if (coords.size() == 2)
    {
      teleport_location.first = true;
      teleport_location.second = {String::to_int(coords.at(0)), String::to_int(coords.at(1))};
    }
  }
}

bool TeleportEffect::blink(CreaturePtr creature, MapPtr current_map, TilePtr old_tile)
{
  bool teleported = false;

  if (creature && current_map && old_tile)
  {
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
    vector<string> keys = get_appropriate_keys(fov_map, teleport_location);
    TilesContainer tiles;
    
    if (fov_map != nullptr)
    {
      tiles = current_map->get_tiles_ref();
    }

    while (!keys.empty() && !teleported)
    {
      string k = keys.back();
      Coordinate c = MapUtils::convert_map_key_to_coordinate(k);
      TilePtr tile = tiles.find(k)->second;

      if (tile && MapUtils::is_tile_available_for_creature(creature, tile))
      {
        MapUtils::add_or_update_location(current_map, creature, c, old_tile);
        teleported = true;
      }

      keys.pop_back();
    }
  }

  if (teleported)
  {
    Game::instance().get_sound()->play(SoundEffectID::TELEPORT);
  }

  return teleported;
}

bool TeleportEffect::teleport(CreaturePtr creature, MapPtr map, TilePtr old_tile)
{
  bool teleported = false;

  if (creature && map && old_tile)
  {
    Dimensions dim = map->size();
    int rows = dim.get_y();
    int cols = dim.get_x();

    // Make a number of attempts to teleport.
    for (int i = 0; i < 100; i++)
    {
      int row = RNG::range(0, rows);
      int col = RNG::range(0, cols);

      Coordinate c(row, col);

      if (teleport_location.first == true)
      {
        c = teleport_location.second;
      }

      TilePtr tile = map->at(c);

      if (tile && !tile->get_creature() && !tile->get_is_blocking(creature))
      {
        MapUtils::add_or_update_location(map, creature, c, old_tile);
        teleported = true;

        break;
      }
    }
  }

  return teleported;
}

vector<string> TeleportEffect::get_appropriate_keys(MapPtr map, const pair<bool, Coordinate>& teleport_loc)
{
  vector<string> keys;

  if (teleport_loc.first == true)
  {
    keys.push_back(MapUtils::convert_coordinate_to_map_key(teleport_loc.second));
  }
  else
  {
    TilesContainer& tiles = map->get_tiles_ref();

    for (const auto& pair : tiles)
    {
      keys.push_back(pair.first);
    }

    shuffle(keys.begin(), keys.end(), RNG::get_engine());
  }

  return keys;
}
