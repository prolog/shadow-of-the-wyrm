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
tuple<bool, int, Rarity> MapCreatureGenerator::generate_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties)
{
  tuple<bool, int, Rarity> creatures_generated(false, 0, Rarity::RARITY_COMMON);

  if (additional_properties.find(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES) != additional_properties.end())
  {
    return generate_initial_set_creatures(map, additional_properties);
  }
  else
  {
    return generate_random_creatures(map, danger_level, additional_properties);
  }
}

tuple<bool, int, Rarity> MapCreatureGenerator::generate_initial_set_creatures(MapPtr map, const std::map<string, string>& additional_properties)
{
  // -1 indicates that there was no generated danger level - a set list of creatures was generated.
  tuple<bool, int, Rarity> creatures_generated(false, -1, Rarity::RARITY_COMMON);

  string initial_creatures = additional_properties.at(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES);
  vector<string> creature_ids = String::create_string_vector_from_csv_string(initial_creatures);

  try
  {
    for (const string& creature_id : creature_ids)
    {
      // JCD FIXME - consider get_coordinate_for_creature here
      std::get<0>(creatures_generated) = MapUtils::place_creature_randomly(map, creature_id);
    }
  }
  catch (...)
  {
    Log::instance().error("MapCreatureGenerator::generate_initial_set_creatures - Attempted to generate initial set creatures, but vector could not be deserialized (this is really bad).");
  }

  return creatures_generated;
}

tuple<bool, int, Rarity> MapCreatureGenerator::generate_random_creatures(MapPtr map, const int base_danger_level, const std::map<string, string>& additional_properties)
{
  tuple<bool, int, Rarity> creatures_generated(false, 0, Rarity::RARITY_COMMON);
  TileType map_terrain_type = map->get_terrain_type();

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  CreatureGenerationManager cgm;
  
  Rarity rarity = CreationUtils::generate_rarity();
  std::get<2>(creatures_generated) = rarity;

  Game& game = Game::instance();

  int max_creatures = CreationUtils::random_maximum_creatures(dim.get_y(), dim.get_x());
  ActionManager am = game.get_action_manager_ref();
  uint num_creatures_to_place = get_num_creatures(map, max_creatures);
  
  uint current_creatures_placed = 0;
  uint unsuccessful_attempts = 0;

  // Generate the list of possible creatures for this map.
  int min_danger_level = RNG::range(1, std::max<int>(1, (base_danger_level / 2)));
  int max_danger_level = get_danger_level(map, base_danger_level);

  if (max_danger_level > min_danger_level)
  {
    min_danger_level = max_danger_level;
  }

  while (RNG::percent_chance(OUT_OF_DEPTH_CREATURES_CHANCE))
  {
    max_danger_level++;

    // If the max danger level has increased, there is also a chance that the
    // rarity will increase, and if so, this will carry over to item generation
    // as well.
    if (rarity == Rarity::RARITY_COMMON)
    {
      rarity = Rarity::RARITY_UNCOMMON;
    }
  }

  CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(map_terrain_type, map->get_permanent(), min_danger_level, max_danger_level, rarity, additional_properties);
  bool out_of_depth_msg_added = false;
  IMessageManager& manager = MessageManagerFactory::instance();

  while (!maximum_creatures_reached(map, current_creatures_placed, num_creatures_to_place) && (unsuccessful_attempts < CreationUtils::MAX_UNSUCCESSFUL_CREATURE_ATTEMPTS))
  {
    CreaturePtr generated_creature = cgm.generate_creature(am, generation_map);

    if (generated_creature)
    {
      Coordinate c = get_coordinate_for_creature(map, generated_creature, rows, cols);

      // Check to see if the spot is empty, and if a creature can be added there.
      TilePtr tile = map->at(c.first, c.second);

      if (MapUtils::is_tile_available_for_creature(generated_creature, tile))
      {
        add_creature_to_map_and_potentially_notify(game, generated_creature, map, manager, base_danger_level, c.first, c.second, current_creatures_placed, creatures_generated, out_of_depth_msg_added);
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

// Get a coordinate for a newly-generated creature.  This will generally be a
// random coordinate, unless the map has preset locations, in which case the
// first of these that is unoccupied will be used.
Coordinate MapCreatureGenerator::get_coordinate_for_creature(MapPtr map, CreaturePtr generated_creature, const int rows, const int cols)
{
  Coordinate c;

  if (map != nullptr)
  {
    vector<Coordinate>& preset_locs = map->get_preset_locations_ref();

    if (preset_locs.empty())
    {
      c.first = RNG::range(0, rows - 1);
      c.second = RNG::range(0, cols - 1);
    }
    else
    {
      vector<Coordinate>::iterator p_it = preset_locs.begin();
      while (p_it != preset_locs.end())
      {
        Coordinate cur_coord = *p_it;

        TilePtr tile = map->at(cur_coord.first, cur_coord.second);

        if (MapUtils::is_tile_available_for_creature(generated_creature, tile))
        {
          c = cur_coord;
          break;
        }
        else
        {
          p_it = preset_locs.erase(p_it);
        }
      }
    }
  }

  return c;
}

// Add the creature to the map.  Update necessary values/counters surrounding
// creature generation.  If the creature is out of depth, potentially add a
// message about this.
void MapCreatureGenerator::add_creature_to_map_and_potentially_notify(Game& game, CreaturePtr generated_creature, MapPtr map, IMessageManager& manager, const int danger_level, const int creature_row, const int creature_col, unsigned int& current_creatures_placed, tuple<bool, int, Rarity>& creatures_generated, bool& out_of_depth_msg_added)
{
  Coordinate coords(creature_row, creature_col);
  GameUtils::add_new_creature_to_map(game, generated_creature, map, coords);

  if (!std::get<0>(creatures_generated))
  {
    std::get<0>(creatures_generated) = true;
  }

  std::get<1>(creatures_generated) = std::max<int>(std::get<1>(creatures_generated), generated_creature->get_level().get_base());

  if (!out_of_depth_msg_added && generated_creature->get_level().get_base() > danger_level)
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DETECTED_OUT_OF_DEPTH_CREATURES));
    manager.send();

    out_of_depth_msg_added = true;
  }

  current_creatures_placed++;
}

// How many creatures should be generated?  Look at both the theoretical maximum,
// and any multiplier present on the map.
int MapCreatureGenerator::get_num_creatures(MapPtr map, const int max_creatures)
{
  int num_creatures = RNG::range(max_creatures / 2, max_creatures);

  if (map != nullptr)
  {
    float multiplier = 1.0f;
    string mult_s = map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE);

    if (!mult_s.empty())
    {
      multiplier = String::to_float(mult_s);
    }

    num_creatures = static_cast<int>(num_creatures * multiplier);
  }

  return num_creatures;
}

// The creature generation rate, if it has been set, also affects the danger level
// at the same rate.
int MapCreatureGenerator::get_danger_level(MapPtr map, const int base_danger_level)
{
  int danger_level = base_danger_level;

  if (map != nullptr)
  {
    float multiplier = 1.0f;
    string mult_s = map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE);

    if (!mult_s.empty())
    {
      multiplier = String::to_float(mult_s);
    }

    danger_level = static_cast<int>(base_danger_level * multiplier);
  }

  return danger_level;
}

bool MapCreatureGenerator::maximum_creatures_reached(MapPtr map, const int current_creatures_placed, const int num_creatures_to_place)
{
  bool max_reached = (current_creatures_placed >= num_creatures_to_place);
  return max_reached;
}