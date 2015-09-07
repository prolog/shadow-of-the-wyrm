#include "ActionTextKeys.hpp"
#include "AutomaticMovementCoordinator.hpp"
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"

using namespace std;

// Attempt to move automatically.
//
// To move automatically, the creature must be allowed to move automatically
// (no bad statuses like hunger, etc), the tile must allow automatic movement
// (not blocking, no creatures, etc), and the FOV must allow automatic
// movement as well (there can't be any hostile creatures that the creature
// can see).
ActionCostValue AutomaticMovementCoordinator::auto_move(CreaturePtr creature, MapPtr map, const Direction d)
{
  // The direction may change during automatic movement, if the creature
  // is e.g., moving down a corridor.
  Direction cur_dir = d;
  Game& game = Game::instance();

  vector<string> message_sids;
  AutomaticMovement& am = creature->get_automatic_movement_ref();
  ActionCostValue auto_move_cost = 0;
  bool auto_movement_engaged = false;
  TilePtr direction_tile = map->at(CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), cur_dir));

  pair<bool, vector<string>> creature_results = creature_can_auto_move(creature);
  bool creature_move = creature_results.first;
  copy(creature_results.second.begin(), creature_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> creature_position_results = creature_position_allows_auto_move(creature, map);
  bool creature_pos_move = creature_position_results.first;
  copy(creature_position_results.second.begin(), creature_position_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> tile_results = tile_allows_auto_move(creature, direction_tile);
  bool tile_move = tile_results.first;
  copy(tile_results.second.begin(), tile_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> map_results = fov_allows_auto_move(creature, creature->get_decision_strategy()->get_fov_map());
  bool map_move = map_results.first;
  copy(map_results.second.begin(), map_results.second.end(), back_inserter(message_sids));

  Coordinate new_coord = CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), cur_dir);
  pair<bool, vector<string>> visit_results = prev_visited_coords_allow_auto_move(creature, new_coord);
  bool visit_move = visit_results.first;

  if (creature_move && creature_pos_move && tile_move && map_move && visit_move)
  {
    set_available_movement_directions(creature, map);
    add_coordinate_to_automove_visited(creature, new_coord);

    MovementAction maction;
    auto_move_cost = maction.move(creature, cur_dir);
    TilePtr new_tile = MapUtils::get_tile_for_creature(map, creature);

    // If the creature was able to move, engage automovement,
    // and track the number of available directions for the
    // next turn.
    if (auto_move_cost > 0)
    {
      auto_movement_engaged = true;
    }

    // Only redraw when the creature actually moves - otherwise, the next turn
    // after disengaging will clear out any messages received at the end of
    // automovement, e.g., from ending on a tile containing items.
    if (creature && creature->get_is_player())
    {
      game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
      game.get_display()->redraw();
    }

  }
  else
  {
    // Clear the automovement available directions to clean things up for
    // next time.
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_AVAILABLE_DIRECTIONS);

    // Now that automovement's done, clear the visited coordinates.
    creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED);

    if (!message_sids.empty())
    {
      string first_message = message_sids.at(0);

      if (!first_message.empty() && creature->get_is_player())
      {
        IMessageManager& manager = MessageManagerFactory::instance();
        manager.add_new_message(StringTable::get(first_message));
        manager.send();
      }
    }
  }

  am.set_direction(cur_dir);
  am.set_engaged(auto_movement_engaged);

  return auto_move_cost;
}

// Check hunger and other attributes on the creature to determine if auto-move
// is allowed.
pair<bool, vector<string>> AutomaticMovementCoordinator::creature_can_auto_move(CreaturePtr creature)
{
  pair<bool, vector<string>> move_details;
  bool can_move = true;
  vector<string> message_sids;

  pair<bool, vector<string>> hunger_details = hunger_allows_auto_move(creature);
  copy(hunger_details.second.begin(), hunger_details.second.end(), back_inserter(message_sids));

  can_move = can_move && hunger_details.first;

  move_details.first = can_move;
  move_details.second = message_sids;

  return move_details;
}

// Does the creature's position (current tile, and the surrounding ones) allow
// auto movement?
pair<bool, vector<string>> AutomaticMovementCoordinator::creature_position_allows_auto_move(CreaturePtr creature, MapPtr map)
{
  pair<bool, vector<string>> move_details = {false, {}};

  TilePtr current_tile = MapUtils::get_tile_for_creature(map, creature);
  bool items_allow_move = false;

  // Stop auto-movement when moving to a tile that has items.
  if (current_tile && current_tile->get_items()->empty())
  {
    items_allow_move = true;
  }

  // Check the last number of available exits to see if it's changed.
  bool has_prior_adjacent_dirs_flag = creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_AVAILABLE_DIRECTIONS);
  uint prev_num_adjacent_dirs = 0;
  
  if (has_prior_adjacent_dirs_flag)
  {
    prev_num_adjacent_dirs = String::to_uint(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_AVAILABLE_DIRECTIONS));
  }

  uint cur_num_adjacent_dirs = MapUtils::get_num_adjacent_movement_directions(map, creature);
  bool exits_allow_move = false;

  // Automovement's good if:
  // - The available directions parameter isn't there (hasn't been set yet)
  // - The parameter is there, and the number of available directions hasn't
  //   been reduced.
  if (!has_prior_adjacent_dirs_flag || (prev_num_adjacent_dirs <= cur_num_adjacent_dirs))
  {
    exits_allow_move = true;
  }

  move_details.first = (items_allow_move && exits_allow_move);
  return move_details;
}

// Check to see if the creature can automatically move, or if they are
// too hungry.
pair<bool, vector<string>> AutomaticMovementCoordinator::hunger_allows_auto_move(CreaturePtr creature)
{
  pair<bool, vector<string>> move_details;

  HungerClock& hunger = creature->get_hunger_clock_ref();

  // The creature can move if it is not the case that the creature's hunger
  // level is at hungry or worse.
  move_details.first = !((hunger.is_normal_or_worse() && (!hunger.is_normal())));
  if (move_details.first == false)
  {
    move_details.second.push_back(ActionTextKeys::ACTION_AUTOMOVE_TOO_HUNGRY);
  }

  return move_details;
}  

// Check to see if the field of view allows automatic movement into it by 
// checking to see if there are any creatures present that are hostile to 
// the creature doing the movement.
pair<bool, vector<string>> AutomaticMovementCoordinator::fov_allows_auto_move(CreaturePtr creature, MapPtr fov_map)
{
  pair<bool, vector<string>> fov_details;
  string automove_creature_id = creature->get_id();

  bool can_move = true;

  // Check the creatures in the FOV to see if any of them are hostile to the
  // creature currently moving.
  map<string, CreaturePtr> fov_creatures = fov_map->get_creatures();
  for(const CreatureMap::value_type& cpair : fov_creatures)
  {
    CreaturePtr fov_creature = cpair.second;
    if (fov_creature->hostile_to(automove_creature_id))
    {
      can_move = false;
      break;
    }
  }

  if (can_move == false)
  {
    fov_details.second.push_back(ActionTextKeys::ACTION_AUTOMOVE_HOSTILE_CREATURES);
  }

  fov_details.first = can_move;
  return fov_details;
}

// Check to see if the tile allows automatic movement into it by checking to 
// see if the tile is available (not empty, no blocking features, etc).
pair<bool, vector<string>> AutomaticMovementCoordinator::tile_allows_auto_move(CreaturePtr creature, TilePtr tile)
{
  pair<bool, vector<string>> tile_details;

  tile_details.first = (MapUtils::is_tile_available_for_creature(creature, tile));

  return tile_details;
}

// Check to see if the creature has already visited the new coordinate.
pair<bool, vector<string>> AutomaticMovementCoordinator::prev_visited_coords_allow_auto_move(CreaturePtr creature, const Coordinate& new_coord)
{
  pair<bool, vector<string>> visit_details = {false, {}};

  if (creature != nullptr)
  {
    vector<string> visited_coords;

    if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED))
    {
      visited_coords = String::create_string_vector_from_csv_string(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED));
    }

    // Has the new coordinate already been visited?  Allow movement if the
    // coordinate has not been visited.
    visit_details.first = (std::find(visited_coords.begin(), visited_coords.end(), MapUtils::convert_coordinate_to_map_key(new_coord)) == visited_coords.end());
  }

  return visit_details;
}

// Set the number of available automatic movement directions.  This is used in
// determining when to stop the automovement algorithm.
void AutomaticMovementCoordinator::set_available_movement_directions(CreaturePtr creature, MapPtr map)
{
  if (creature != nullptr && map != nullptr)
  {
    uint num_available_move_dirs = MapUtils::get_num_adjacent_movement_directions(map, creature);
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_AVAILABLE_DIRECTIONS, std::to_string(num_available_move_dirs));
  }
}

// Add a coordinate to the current set of coordinates visited during 
// automovement, so that the same coordinate can't be visited twice
// (no running loops!).
void AutomaticMovementCoordinator::add_coordinate_to_automove_visited(CreaturePtr creature, const Coordinate& c)
{
  if (creature != nullptr)
  {
    vector<string> coords;

    if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED))
    {
      coords = String::create_string_vector_from_csv_string(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED));
    }

    coords.push_back(MapUtils::convert_coordinate_to_map_key(c));
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED, String::create_csv_from_string_vector(coords));
  }
}