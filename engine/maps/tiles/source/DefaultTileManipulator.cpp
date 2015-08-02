#include "DefaultTileManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureGenerationManager.hpp"
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemGenerationManager.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

const int DefaultTileManipulator::UNDEAD_LEVEL_UPPER_BOUND_OFFSET = 5;

DefaultTileManipulator::DefaultTileManipulator()
  : super_type_message_sids({ { TileSuperType::TILE_SUPER_TYPE_GROUND, ActionTextKeys::ACTION_DIG_GROUND },
                             { TileSuperType::TILE_SUPER_TYPE_WATER, ActionTextKeys::ACTION_DIG_WATER },
                             { TileSuperType::TILE_SUPER_TYPE_AIR, ActionTextKeys::ACTION_DIG_AIR } })
{
}

// Add a default digging message based on the creature and the tile super
// type - "Splash!" for water, "Whoosh!" for air, etc.
bool DefaultTileManipulator::dig(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  bool dug = false;

  if (creature != nullptr && tile != nullptr)
  {
    TileSuperType super_type = tile->get_tile_super_type();

    if (creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();

      auto s_it = super_type_message_sids.find(super_type);
      if (s_it != super_type_message_sids.end())
      {
        manager.add_new_message(StringTable::get(super_type_message_sids[super_type]));
        manager.send();
      }
    }

    // Only add undead/items if the tile has not been dug already.
    if (!(tile->get_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG) == Bool::to_string(true)))
    {
      add_undead_if_necessary(creature, map, tile);
      add_item_if_necessary(creature, map, tile);
    }

    dug = true;
  }

  return dug;
}

// Potentially add an undead creature around the creature doing the digging.
void DefaultTileManipulator::add_undead_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  if (tile != nullptr)
  {
    if (RNG::percent_chance(tile->get_dig_chances().get_pct_chance_undead()))
    {
      int min_danger_level = std::max<int>(1, creature->get_level().get_current() / 2);
      int max_danger_level = std::max<int>(1, map->get_danger()) + UNDEAD_LEVEL_UPPER_BOUND_OFFSET;

      Game& game = Game::instance();
      CreaturePtr undead;
      CreatureGenerationManager cgm;
      std::map<string, string> additional_properties = { { MapProperties::MAP_PROPERTIES_GENERATED_CREATURE_RACE_ID, "_undead" } };
      CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(tile->get_tile_type(), map->get_permanent(), min_danger_level, max_danger_level, Rarity::RARITY_VERY_RARE, additional_properties);

      undead = cgm.generate_creature(game.get_action_manager_ref(), generation_map);
      
      if (undead != nullptr)
      {
        // Add the undead to the map: randomize the adjacent tiles, and then
        // iterate through the tiles, trying to place.
        bool placed = false;

        TileDirectionMap directions = MapUtils::get_adjacent_tiles_to_creature(map, creature);
        vector<Direction> keys;
        for (const auto& d : directions)
        {
          keys.push_back(d.first);
        }

        std::random_shuffle(keys.begin(), keys.end());

        for (const auto& direction : keys)
        {
          TilePtr tile = directions.at(direction);

          if (tile != nullptr && !tile->has_creature())
          {
            Coordinate undead_coords = CoordUtils::get_new_coordinate(MapUtils::get_coordinate_for_creature(map, creature), direction);
            GameUtils::add_new_creature_to_map(game, undead, map, undead_coords);

            placed = true;
            break;
          }
        }

        // Add a message about the dead rising...
        if (placed && creature->get_is_player())
        {
          IMessageManager& manager = MessageManagerFactory::instance();

          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_UNDEAD_FOUND));
          manager.send();
        }
      }
    }
  }
}

// Potentially add an item to the tile being digged.
// As valuable items are often buried, any item within the danger level
// range can be found via digging.
void DefaultTileManipulator::add_item_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  if (tile != nullptr)
  {
    if (RNG::percent_chance(tile->get_dig_chances().get_pct_chance_item()))
    {
      int danger_level = map->get_danger();

      ItemGenerationManager igm;
      ItemGenerationVec igv = igm.generate_item_generation_vec(1, std::max<int>(danger_level, creature->get_level().get_current()), Rarity::RARITY_VERY_RARE);

      Game& game = Game::instance();
      ActionManager am = game.get_action_manager_ref();

      ItemPtr item = igm.generate_item(am, igv, RNG::range(1, static_cast<int>(danger_level / 2)));
      tile->get_items()->add(item);

      if (creature->get_is_player())
      {
        IMessageManager& manager = MessageManagerFactory::instance();

        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_ITEM_FOUND));
        manager.send();
      }
    }
  }
}


