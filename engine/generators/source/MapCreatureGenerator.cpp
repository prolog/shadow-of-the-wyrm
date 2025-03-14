#include "ActionTextKeys.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "FollowerCalculator.hpp"
#include "MapCreatureGenerator.hpp"
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "CreationUtils.hpp"
#include "CreatureGenerationManager.hpp"
#include "GameUtils.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "TileMovementConfirmation.hpp"

using namespace std;

const int MapCreatureGenerator::OUT_OF_DEPTH_CREATURES_CHANCE = 15;
const int MapCreatureGenerator::PACK_TILE_CHANCE = 90;

// Generate the creatures.  Returns true if creatures were created, false otherwise.
tuple<bool, int, Rarity> MapCreatureGenerator::generate_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties)
{
  tuple<bool, int, Rarity> creatures_generated(false, 0, Rarity::RARITY_COMMON);

  if (map && map->get_allow_creature_creation())
  {
    if (additional_properties.find(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES) != additional_properties.end())
    {
      return generate_initial_set_creatures(map, additional_properties);
    }
    else
    {
      return generate_random_creatures(map, danger_level, additional_properties);
    }
  }

  return creatures_generated;
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

tuple<bool, int, Rarity> MapCreatureGenerator::generate_random_creatures(MapPtr map, const int base_danger, const std::map<string, string>& additional_properties)
{
  tuple<bool, int, Rarity> creatures_generated(false, 0, Rarity::RARITY_COMMON);
  TileType map_terrain_type = map->get_terrain_type();
  set<TileType> map_terrain_types = { map_terrain_type };
  vector<TileType> secondary_types = map->get_secondary_terrain();

  int base_danger_level = base_danger;
  if (map != nullptr)
  {
    string dlvl_override = map->get_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE);
    if (!dlvl_override.empty())
    {
      base_danger_level = String::to_int(dlvl_override);
    }
  }

  for (const auto& tt : secondary_types)
  {
    map_terrain_types.insert(tt);
  }

  Dimensions dim = map->size();
  CreatureGenerationManager cgm;
  
  Rarity rarity = CreationUtils::generate_rarity();
  std::get<2>(creatures_generated) = rarity;

  Game& game = Game::instance();

  int max_creatures = CreationUtils::random_maximum_creatures(dim.get_y(), dim.get_x());
  ActionManager& am = game.get_action_manager_ref();
  uint num_creatures_to_place = get_num_creatures(map, max_creatures);
  
  uint current_creatures_placed = 0;
  uint unsuccessful_attempts = 0;

  auto fd_it = additional_properties.find(MapProperties::MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED);
  if (fd_it != additional_properties.end())
  {
    map->set_property(fd_it->first, fd_it->second);
  }

  int min_danger_level = get_min_danger_level(map, base_danger_level);
  int max_danger_level = get_danger_level(map, base_danger_level);

  if (min_danger_level > max_danger_level)
  {
    min_danger_level = max_danger_level;
  }

  // Generate the list of possible creatures for this map.
  while (RNG::percent_chance(get_pct_chance_out_of_depth_creatures(map)))
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

  CreatureGenerationIndex generation_index;
  bool allow_ancient_beasts = false;
  auto ab_it = additional_properties.find(MapProperties::MAP_PROPERTIES_ANCIENT_BEASTS);
  
  if (ab_it != additional_properties.end())
  {
    allow_ancient_beasts = String::to_bool(ab_it->second);
  }

  while (generation_index.empty() && min_danger_level >= 1)
  {
    generation_index = cgm.generate_creature_generation_map(map_terrain_types, map->get_permanent(), map->is_islet(), map->get_map_type(), min_danger_level, max_danger_level, rarity, additional_properties);

    if (generation_index.empty())
    {
      if (allow_ancient_beasts)
      {
        break;
      }

      min_danger_level /= 2;
    }
  }

  CreatureGenerationList generation_list = generation_index.get();

  if (generation_list.empty())
  {
    MapType map_type = map->get_map_type();
    generation_list = cgm.generate_ancient_beasts(max_danger_level, map_type, map_terrain_type).get();
  }

  IMessageManager& manager = MMF::instance();
  CreatureFactory cf;
  CreatureGenerationValuesMap& cgvm = game.get_creature_generation_values_ref();
  TileMovementConfirmation tmc;
  pair<Coordinate, Coordinate> coord_range = map->get_generation_coordinates();

  // Final sanity check before we try to start generating.
  if (generation_list.empty())
  {
    return creatures_generated;
  }

  place_followers(map, coord_range, game, am, manager, base_danger_level, current_creatures_placed, creatures_generated);

  while (!generation_list.empty() && !maximum_creatures_reached(map, current_creatures_placed, num_creatures_to_place) && (unsuccessful_attempts < CreationUtils::MAX_UNSUCCESSFUL_CREATURE_ATTEMPTS))
  {
    CreaturePtr generated_creature = cgm.generate_creature(am, generation_list, map);

    if (generated_creature)
    {
      auto c_it = cgvm.find(generated_creature->get_original_id());
      Coordinate c = get_coordinate_for_creature(map, generated_creature, coord_range);

      // Check to see if the spot is empty, and if a creature can be added there.
      TilePtr tile = map->at(c.first, c.second);

      if (MapUtils::is_tile_available_for_creature(generated_creature, tile) &&
          !tmc.get_confirmation_details(generated_creature, map, nullptr, c, tile, c).get_require_prompt() &&
          MapUtils::does_area_around_tile_allow_creature_generation(map, c))
      {
        //  If pack creatures are generated, the maximum for the level is
        // adjusted as well.
        int addl_pack_creatures = 0;
        bool can_generate_pack = false;

        if (c_it != cgvm.end())
        {
          can_generate_pack = (c_it->second.is_maximum_reached() == false);
        }

        CreatureCalculator cc;
        if (can_generate_pack && RNG::percent_chance(cc.get_pct_chance_pack(generated_creature)))
        {
          // Pack generation: packs are meaner, are not suppressed from appearing
          // by stairs.
          string creature_id = generated_creature->get_original_id();
          vector<Coordinate> coords = CoordUtils::get_adjacent_map_coordinates(map->size(), c.first, c.second);

          for (const Coordinate& adj : coords)
          {
            TilePtr ptile = map->at(adj);
            CreaturePtr pack_creature = cf.create_by_creature_id(am, creature_id, map, generated_creature);

            if (pack_creature != nullptr)
            {
              if (RNG::percent_chance(PACK_TILE_CHANCE) &&
                  MapUtils::is_tile_available_for_creature(pack_creature, ptile) && 
                 !tmc.get_confirmation_details(pack_creature, map, nullptr, adj, ptile, adj).get_require_prompt())
              {
                addl_pack_creatures++;
                add_creature_to_map(game, pack_creature, map, manager, base_danger_level, adj.first, adj.second, current_creatures_placed, creatures_generated);
              }
              else
              {
                // Creature was generated, but we can't place it - decrement
                // the creature count.
                c_it->second.decr_current();
              }
            }
          }
        }

        // Regular creature generation: away from stairs.
        // When there's no pack, this will always be called.
        // When there's a pack, this creature will just be at the centre.
        add_creature_to_map(game, generated_creature, map, manager, base_danger_level, c.first, c.second, current_creatures_placed, creatures_generated);

        // Ensure that pack creatures don't count against the level's maximum.
        num_creatures_to_place += addl_pack_creatures;
      }
      else
      {
        // Creature was generated, but we can't place it - decrement
        // the creature count so that uniques aren't suppressed.  Only
        // do this if we're not dealing with an ancient beast, which
        // can be generated in any quantity.
        if (c_it != cgvm.end())
        {
          c_it->second.decr_current();
        }

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
Coordinate MapCreatureGenerator::get_coordinate_for_creature(MapPtr map, CreaturePtr generated_creature, const pair<Coordinate, Coordinate>& coord_range)
{
  Coordinate c = CoordUtils::end();

  if (map != nullptr && generated_creature != nullptr)
  {
    vector<Coordinate>& preset_locs = map->get_preset_locations_ref();

    if (preset_locs.empty())
    {
      if (generated_creature->can_breathe(BreatheType::BREATHE_TYPE_WATER))
      {
        vector<TileType> secondary = map->get_secondary_terrain();

        if (!secondary.empty() && std::find(secondary.begin(), secondary.end(), TileType::TILE_TYPE_SEA) != secondary.end())
        {
          c = MapUtils::get_random_coastline_coordinate(map);
        }
      }

      if (CoordUtils::is_end(c))
      {
        c.first = RNG::range(coord_range.first.first, coord_range.second.first);
        c.second = RNG::range(coord_range.first.second, coord_range.second.second);
      }
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
// creature generation.
void MapCreatureGenerator::add_creature_to_map(Game& game, CreaturePtr generated_creature, MapPtr map, IMessageManager& /*manager*/, const int /*danger_level*/, const int creature_row, const int creature_col, unsigned int& current_creatures_placed, tuple<bool, int, Rarity>& creatures_generated)
{
  Coordinate coords(creature_row, creature_col);
  GameUtils::add_new_creature_to_map(game, generated_creature, map, coords);

  if (!std::get<0>(creatures_generated))
  {
    std::get<0>(creatures_generated) = true;
  }

  std::get<1>(creatures_generated) = std::max<int>(std::get<1>(creatures_generated), generated_creature->get_level().get_base());

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

// Most of the time, the minimum danger level is somewhere between 1 and half
// the base danger.  But certain maps have fixed danger levels for creature
// generation.
int MapCreatureGenerator::get_min_danger_level(MapPtr map, const int base_danger_level)
{
  int min_danger_level = RNG::range(std::max<int>(1, base_danger_level / 2), base_danger_level);
  
  if (map != nullptr)
  {
    string fixed_cr_dlvl = map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED);

    if (!fixed_cr_dlvl.empty() && String::to_bool(fixed_cr_dlvl))
    {
      min_danger_level = base_danger_level;
    }
  }

  return min_danger_level;
}

// The creature generation rate, if it has been set, also affects the danger level
// at the same rate.
int MapCreatureGenerator::get_danger_level(MapPtr map, const int base_danger_level)
{
  int danger_level = base_danger_level;

  if (map != nullptr)
  {
    string fixed_cr_dlvl = map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED);

    if (!fixed_cr_dlvl.empty() && String::to_bool(fixed_cr_dlvl))
    {
      danger_level = base_danger_level;
    }
    else
    {
      float multiplier = 1.0f;
      string mult_s = map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE);

      if (!mult_s.empty())
      {
        multiplier = String::to_float(mult_s);
      }

      danger_level = static_cast<int>(base_danger_level * multiplier);
    }
  }

  return danger_level;
}

int MapCreatureGenerator::get_pct_chance_out_of_depth_creatures(MapPtr map)
{
  int ood = OUT_OF_DEPTH_CREATURES_CHANCE;

  if (map != nullptr)
  {
    string fixed_cr_dlvl = map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED);

    if (!fixed_cr_dlvl.empty() && String::to_bool(fixed_cr_dlvl))
    {
      ood = 0;
    }
  }

  return ood;
}

bool MapCreatureGenerator::maximum_creatures_reached(MapPtr /*map*/, const int current_creatures_placed, const int num_creatures_to_place)
{
  bool max_reached = (current_creatures_placed >= num_creatures_to_place);
  return max_reached;
}

void MapCreatureGenerator::place_followers(MapPtr map, const pair<Coordinate, Coordinate>& coord_range, Game& game, ActionManager& am, IMessageManager& manager, const int base_danger_level, uint& current_creatures_placed, tuple<bool, int, Rarity>& creatures_generated)
{
  CreatureGenerationManager cgm;
  FollowerCalculator fc;
  Depth d = map->size().depth();
  const int num_attempts = 20;
  MapType map_type = map ? map->get_map_type() : MapType::MAP_TYPE_OVERWORLD;

  if (map_type == MapType::MAP_TYPE_OVERWORLD || map_type == MapType::MAP_TYPE_UNDERWORLD)
  {
    if (RNG::x_in_y_chance(fc.calculate_x_in_y_chance_adventurer(d)))
    {
      int num_adv = RNG::range(1, 2);

      for (int adv = 0; adv < num_adv; adv++)
      {
        CreaturePtr adventurer = cgm.generate_follower(am, map, FollowerType::FOLLOWER_TYPE_ADVENTURER, CreatureGenerationManager::ADVENTURER_DEFAULT_LEVEL);

        for (int i = 0; i < num_attempts; i++)
        {
          bool placed = place_follower(adventurer, map, coord_range, game, am, manager, base_danger_level, current_creatures_placed, creatures_generated);

          if (placed)
          {
            break;
          }
        }
      }
    }

    if (RNG::x_in_y_chance(fc.calculate_x_in_y_chance_hireling(d)))
    {
      CreaturePtr hireling = cgm.generate_follower(am, map, FollowerType::FOLLOWER_TYPE_HIRELING, RNG::range(CreatureGenerationManager::HIRELING_MIN_LEVEL, CreatureGenerationManager::HIRELING_MAX_LEVEL));

      for (int i = 0; i < num_attempts; i++)
      {
        bool placed = place_follower(hireling, map, coord_range, game, am, manager, base_danger_level, current_creatures_placed, creatures_generated);

        if (placed)
        {
          break;
        }
      }
    }
  }
}

bool MapCreatureGenerator::place_follower(CreaturePtr creature, MapPtr map, const pair<Coordinate, Coordinate>& coord_range, Game& game, ActionManager& /*am*/, IMessageManager& manager, const int base_danger_level, uint& current_creatures_placed, tuple<bool, int, Rarity>& creatures_generated)
{
  bool placed = false;

  if (creature != nullptr && map != nullptr)
  {
    Coordinate c = get_coordinate_for_creature(map, creature, coord_range);

    // Check to see if the spot is empty, and if a creature can be added there.
    TilePtr tile = map->at(c.first, c.second);

    if (MapUtils::is_tile_available_for_creature(creature, tile) &&
        MapUtils::does_area_around_tile_allow_creature_generation(map, c))
    {
      add_creature_to_map(game, creature, map, manager, base_danger_level, c.first, c.second, current_creatures_placed, creatures_generated);
      placed = true;
    }
  }

  return placed;
}