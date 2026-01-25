#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "CreatureFactory.hpp"
#include "GameUtils.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

using namespace std;

GameUtils::GameUtils()
{
}

void GameUtils::make_map_permanent(Game& game, CreaturePtr creature, MapPtr current_map)
{
  if (current_map != nullptr)
  {
    current_map->set_permanent(true);
    string current_map_id = current_map->get_map_id();
    game.get_map_registry_ref().set_map(current_map_id, current_map);

    // Assumption: if a creature (realistically, the player) is in a
    // previously-random map on the overworld, it is connected to
    // the player's position on that map.
    MapPtr world_map = game.get_map_registry_ref().get_map(MapID::MAP_ID_WORLD_MAP);

    if (world_map != nullptr)
    {
      Coordinate location = world_map->get_location(creature->get_id());
      TilePtr creature_wm_tile = world_map->at(location);

      if (creature_wm_tile != nullptr)
      {
        string wm_custom_map_id = creature_wm_tile->get_custom_map_id();

        if (wm_custom_map_id.empty())
        {
          creature_wm_tile->set_custom_map_id(current_map_id);
        }
      }
    }
  }
}

// Add a new creature to the specified map.  If the specified map is the
// currently loaded map, ensure that the creature is also added
// appropriately to the Game's ActionCoordinator.
void GameUtils::add_new_creature_to_map(Game& game, CreaturePtr new_creature, MapPtr map, const Coordinate& coords)
{
  if (new_creature != nullptr)
  {
    // Add the creature to the map.
    MapUtils::add_or_update_location(map, new_creature, coords);

    // If it has any followers, place them too.  Grab the list of IDs so we
    // can update the action coordinator, then add the new creature as well.
    vector<string> new_creature_ids = MapUtils::place_followers(map, new_creature, coords);
    new_creature_ids.push_back(new_creature->get_id());

    // Potentially add the creature(s) to the action coordinator, if the
    // map is the current game map.
    MapPtr game_current_map = game.get_current_map();

    if (game_current_map != nullptr && map->get_map_id() == game_current_map->get_map_id())
    {
      for (const string& id : new_creature_ids)
      {
        ActionCoordinator& ac = game.get_action_coordinator_ref();
        ActionCost cost = ac.get_current_action_cost();
        cost.set_cost(cost.get_cost() + 1);

        // Set the action cost to one more than the current.
        ac.add(cost, id);
      }
    }
  }
}

void GameUtils::summon_creatures(CreaturePtr creature, MapPtr map, const std::pair<Dice, std::vector<std::string>>& summoned_creature_details, const string& message_sid)
{
  // Guard to ensure there's something to actually summon.
  if (summoned_creature_details.second.empty() ||
      summoned_creature_details.second.at(0).empty())
  {
    return;
  }

  if (creature != nullptr && map != nullptr)
  {
    Dice num_creatures = summoned_creature_details.first;
    vector<string> possible_creatures = summoned_creature_details.second;
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
    TilesContainer& tiles = fov_map->get_tiles_ref();

    vector<pair<string, TilePtr>> free_tiles;

    // Make a list of the free tiles surrounding the caster.  These will
    // be available for randomly placing the summoned creatures, as long
    // as the tiles can support the creature.
    for (TilesContainer::value_type& fov_map_tile : tiles)
    {
      TilePtr tile = fov_map_tile.second;
      if (tile && !tile->get_is_blocking())
      {
        free_tiles.push_back(fov_map_tile);
      }
    }

    // Roll the num_creatures dice to get the number of creatures to
    // place.
    int n_creatures = RNG::dice(num_creatures);
    int cur_creatures_placed = 0;

    // Place n summoned creatures on the free tiles surrounding the
    // caster.  Stop if there are no more free tiles available.
    size_t pcreatures_size = possible_creatures.size();

    bool creatures_summoned = false;
    int max_failed_attempts = 3;
    int failed_attempts = 0;

    if (pcreatures_size > 0)
    {
      while ((failed_attempts < max_failed_attempts) &&
             (cur_creatures_placed < n_creatures) && 
             (!free_tiles.empty()))
      {
        // Select a tile at random
        int tile_idx = RNG::range(0, free_tiles.size() - 1);
        string creature_id = possible_creatures.at(RNG::range(0, pcreatures_size - 1));

        // Create a creature to place.
        CreatureFactory cf;
        CreaturePtr summoned_creature = cf.create_by_creature_id(game.get_action_manager_ref(), creature_id, current_map);

        if (summoned_creature != nullptr)
        {
          // Place the creature on the tile
          pair<string, TilePtr> fov_tile = free_tiles.at(tile_idx);
          Coordinate coords = MapUtils::convert_map_key_to_coordinate(fov_tile.first);
          TilePtr tile = fov_tile.second;

          // Add the newly-summoned creature to the map, adding it as well to the
          // action coordinator if necessary.
          GameUtils::add_new_creature_to_map(game, summoned_creature, current_map, coords);

          // Remove the tile from the list of free tiles, and increment the number
          // of summoned creatures.
          free_tiles.erase(free_tiles.begin() + tile_idx);
          cur_creatures_placed++;

          if (creatures_summoned == false)
          {
            creatures_summoned = true;
          }
        }
        else
        {
          failed_attempts++;
        }
      }

      // Add an appropriate message.
      IMessageManager& manager = MMF::instance();
      manager.add_new_message(StringTable::get(message_sid));
      manager.send();
    }
  }
}

void GameUtils::move_to_new_map(TilePtr current_tile, MapPtr old_map, MapPtr new_map, MapExitPtr map_exit)
{
  if (current_tile != nullptr && old_map != nullptr && new_map != nullptr)
  {
    // Remove the creature from its present tile, and from the temporary
    // vector of creatures as well.
    CreaturePtr current_creature = current_tile->get_creature();
    MapUtils::serialize_and_remove_followers(old_map, new_map, current_creature);
    MapUtils::remove_creature(old_map, current_creature);

    Coordinate c = CoordUtils::end();

    if (map_exit && map_exit->has_coordinate() && new_map->get_permanent())
    {
      c = map_exit->get_coordinate();
    }
    else if (map_exit == nullptr && new_map->get_permanent() && current_tile->has_additional_property(TileProperties::TILE_PROPERTY_LINKED_COORD))
    {
      c = String::create_coordinate_from_string(current_tile->get_additional_property(TileProperties::TILE_PROPERTY_LINKED_COORD));
    }

    Coordinate new_map_prev_loc = MapUtils::place_creature(new_map, current_creature, current_creature->get_id(), c);
    MapUtils::set_multi_map_entry_details(new_map, old_map, new_map_prev_loc);

    MapUtils::place_followers(new_map, current_creature, new_map_prev_loc);

    if (MapUtils::should_link_entry_point(new_map->get_map_type()))
    {
      // If there's an exit, link it to the creature's location on the new map
      // so it can be easily found later.
      if (map_exit != nullptr)
      {
        map_exit->set_coordinate(new_map_prev_loc);
      }
      else
      {
        current_tile->set_additional_property(TileProperties::TILE_PROPERTY_LINKED_COORD, String::create_string_from_coordinate(new_map_prev_loc));
      }
    }

    // Set the new map to be loaded in the next iteration of the game loop.
    Game& game = Game::instance();
    game.set_current_map(new_map);
    game.reload_map();

    SoundPtr sound = game.get_sound();
    sound->play(SoundEffectID::EXIT_MAP);
    sound->play_music(new_map);
  }
}

// Check to see if a particular creature exists within the player's view map.
bool GameUtils::is_creature_in_player_view_map(Game& game, const string& creature_id)
{
  bool creature_in_view_map = false;

  MapPtr map = game.get_current_map();
  CreaturePtr player = game.get_current_player();

  if (player)
  {
    MapPtr view_map = player->get_decision_strategy()->get_fov_map();

    if (view_map)
    {
      // Rebuild the view map's creatures in case it is out of date - the player 
      // might not have acted in some time...
      std::map<string, CreaturePtr>& creatures = view_map->get_creatures_cref();

      creature_in_view_map = (creatures.find(creature_id) != creatures.end());
    }
  }

  return creature_in_view_map;
}

// Check to see if two creature are adjacent on the current map.
bool GameUtils::is_creature_adjacent(Game& game, CreaturePtr creature1, CreaturePtr creature2)
{
  bool creatures_adjacent = false;
  MapPtr map = game.get_current_map();

  if (creature1 && creature2)
  {
    Coordinate c1 = map->get_location(creature1->get_id());
    Coordinate c2 = map->get_location(creature2->get_id());

    creatures_adjacent = CoordUtils::are_coordinates_adjacent(c1, c2);
  }

  return creatures_adjacent;
}

// Is the player among the creatures provided?
bool GameUtils::is_player_among_creatures(CreaturePtr creature1, CreaturePtr creature2)
{
  return ((creature1 && creature1->get_is_player()) || (creature2 && creature2->get_is_player()));
}

// How many seconds since the game started?
double GameUtils::get_seconds(Game& game)
{
  double sec = 0.0;
  World* world = game.get_current_world();

  if (world != nullptr)
  {
    sec = world->get_calendar().get_seconds();
  }

  return sec;
}

bool GameUtils::is_magic_category_possible(const SkillType magic_category)
{
  std::set<SkillType> possible_categories = { SkillType::SKILL_MAGIC_CANTRIPS, SkillType::SKILL_MAGIC_ARCANE, SkillType::SKILL_MAGIC_MYSTIC, SkillType::SKILL_MAGIC_PRIMORDIAL };

  if (magic_category == SkillType::SKILL_MAGIC_DIVINE)
  {
    return Game::instance().do_deities_exist();
  }

  return (possible_categories.find(magic_category) != possible_categories.end());
}

Date GameUtils::get_date(Game& game)
{
  Date d = Date::null();

  World* world = game.get_current_world();

  if (world != nullptr)
  {
    d = world->get_calendar().get_date();
  }

  return d;
}

StartingLocation GameUtils::get_random_starting_location(const StartingLocationMap& sm)
{
  StartingLocation sl;

  int rnd_idx = RNG::range(0, sm.size() - 1);
  int cnt = 0;

  for (auto sm_it = sm.begin(); sm_it != sm.end(); sm_it++)
  {
    if (cnt == rnd_idx)
    {
      sl = sm_it->second;
      break;
    }

    cnt++;
  }

  return sl;
}