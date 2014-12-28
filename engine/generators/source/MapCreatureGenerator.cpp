#include "MapCreatureGenerator.hpp"
#include "Conversion.hpp"
#include "CreationUtils.hpp"
#include "CreatureGenerationManager.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

using namespace std;

// Generate the creatures.  Returns true if creatures were created, false otherwise.
bool MapCreatureGenerator::generate_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties)
{
  bool creatures_generated = false;

  if (additional_properties.find(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES) != additional_properties.end())
  {
    return generate_initial_set_creatures(map, additional_properties);
  }
  else
  {
    return generate_random_creatures(map, danger_level, additional_properties);
  }
}

bool MapCreatureGenerator::generate_initial_set_creatures(MapPtr map, const std::map<string, string>& additional_properties)
{
  bool creatures_generated = false;

  string initial_creatures = additional_properties.at(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES);
  vector<string> creature_ids = String::create_string_vector_from_csv_string(initial_creatures);

  try
  {
    for (const string& creature_id : creature_ids)
    {
      creatures_generated = MapUtils::place_creature_randomly(map, creature_id);
    }
  }
  catch (...)
  {
    Log::instance().error("MapCreatureGenerator::generate_initial_set_creatures - Attempted to generate initial set creatures, but vector could not be deserialized (this is really bad).");
  }

  return creatures_generated;
}

bool MapCreatureGenerator::generate_random_creatures(MapPtr map, const int danger_level, const std::map<string, string>& additional_properties)
{
  bool creatures_generated = false;
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
  CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(map_terrain_type, map->get_permanent(), min_danger_level, danger_level, rarity);

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
        Coordinate coords(creature_row, creature_col);
        MapUtils::add_or_update_location(map, generated_creature, coords);
        if (!creatures_generated) creatures_generated = true;
        current_creatures_placed++;
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

