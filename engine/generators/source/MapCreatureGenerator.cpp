#include "ActionTextKeys.hpp"
#include "MapCreatureGenerator.hpp"
#include "Conversion.hpp"
#include "CreationUtils.hpp"
#include "CreatureGenerationManager.hpp"
#include "GameUtils.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

using namespace std;

const int MapCreatureGenerator::OUT_OF_DEPTH_CREATURES_CHANCE = 15;

// Generate the creatures.  Returns true if creatures were created, false otherwise.
pair<bool, int> MapCreatureGenerator::generate_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties)
{
  pair<bool, int> creatures_generated(false, 0);

  if (additional_properties.find(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES) != additional_properties.end())
  {
    return generate_initial_set_creatures(map, additional_properties);
  }
  else
  {
    return generate_random_creatures(map, danger_level, additional_properties);
  }
}

pair<bool, int> MapCreatureGenerator::generate_initial_set_creatures(MapPtr map, const std::map<string, string>& additional_properties)
{
  // -1 indicates that there was no generated danger level - a set list of creatures was generated.
  pair<bool, int> creatures_generated(false, -1);

  string initial_creatures = additional_properties.at(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES);
  vector<string> creature_ids = String::create_string_vector_from_csv_string(initial_creatures);

  try
  {
    for (const string& creature_id : creature_ids)
    {
      creatures_generated.first = MapUtils::place_creature_randomly(map, creature_id);
    }
  }
  catch (...)
  {
    Log::instance().error("MapCreatureGenerator::generate_initial_set_creatures - Attempted to generate initial set creatures, but vector could not be deserialized (this is really bad).");
  }

  return creatures_generated;
}

pair<bool, int> MapCreatureGenerator::generate_random_creatures(MapPtr map, const int danger_level, const std::map<string, string>& additional_properties)
{
  pair<bool, int> creatures_generated(false, 0);
  TileType map_terrain_type = map->get_terrain_type();

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  CreatureGenerationManager cgm;
  
  Rarity rarity = CreationUtils::generate_rarity();

  Game& game = Game::instance();

  int max_creatures = CreationUtils::random_maximum_creatures(dim.get_y(), dim.get_x());
  ActionManager am = game.get_action_manager_ref();
  uint num_creatures_to_place = RNG::range(max_creatures / 2, max_creatures);
  uint current_creatures_placed = 0;
  uint unsuccessful_attempts = 0;

  // Generate the list of possible creatures for this map.
  int min_danger_level = RNG::range(1, std::max<int>(1, (danger_level / 2)));
  int max_danger_level = danger_level;
  while (RNG::percent_chance(OUT_OF_DEPTH_CREATURES_CHANCE))
  {
    max_danger_level++;
  }

  CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(map_terrain_type, map->get_permanent(), min_danger_level, max_danger_level, rarity, additional_properties);
  bool out_of_depth_msg_added = false;
  IMessageManager& manager = MessageManagerFactory::instance();

  while ((current_creatures_placed < num_creatures_to_place) && (unsuccessful_attempts < CreationUtils::MAX_UNSUCCESSFUL_CREATURE_ATTEMPTS))
  {
    CreaturePtr generated_creature = cgm.generate_creature(am, generation_map);

    if (generated_creature)
    {
      int creature_row = RNG::range(0, rows - 1);
      int creature_col = RNG::range(0, cols - 1);

      // Check to see if the spot is empty, and if a creature can be added there.
      TilePtr tile = map->at(creature_row, creature_col);

      if (MapUtils::is_tile_available_for_creature(generated_creature, tile))
      {
        add_creature_to_map_and_potentially_notify(game, generated_creature, map, manager, danger_level, creature_row, creature_col, current_creatures_placed, creatures_generated, out_of_depth_msg_added);
      }
      else
      {
        unsuccessful_attempts++;
      }
    }
    else
    {
      unsuccessful_attempts++;
    }
  }

  return creatures_generated;
}

// Add the creature to the map.  Update necessary values/counters surrounding
// creature generation.  If the creature is out of depth, potentially add a
// message about this.
void MapCreatureGenerator::add_creature_to_map_and_potentially_notify(Game& game, CreaturePtr generated_creature, MapPtr map, IMessageManager& manager, const int danger_level, const int creature_row, const int creature_col, unsigned int& current_creatures_placed, pair<bool, int>& creatures_generated, bool& out_of_depth_msg_added)
{
  Coordinate coords(creature_row, creature_col);
  GameUtils::add_new_creature_to_map(game, generated_creature, map, coords);

  if (!creatures_generated.first)
  {
    creatures_generated.first = true;
  }

  creatures_generated.second = std::max<int>(creatures_generated.second, generated_creature->get_level().get_base());

  if (!out_of_depth_msg_added && generated_creature->get_level().get_base() > danger_level)
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DETECTED_OUT_OF_DEPTH_CREATURES));
    manager.send();

    out_of_depth_msg_added = true;
  }

  current_creatures_placed++;
}