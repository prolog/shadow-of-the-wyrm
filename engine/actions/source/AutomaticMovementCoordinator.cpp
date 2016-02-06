#include "ActionTextKeys.hpp"
#include "AutomaticMovementCoordinator.hpp"
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "DirectionUtils.hpp"
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
ActionCostValue AutomaticMovementCoordinator::auto_move(CreaturePtr creature, MapPtr map, const Direction d, const AutomaticMovementFlags& amf)
{
  // The direction may change during automatic movement, if the creature
  // is e.g., moving down a corridor.
  Direction cur_dir = d;
  Game& game = Game::instance();

  vector<string> message_sids;
  AutomaticMovement& am = creature->get_automatic_movement_ref();

  // Set the direction so it can be properly considered for creature_position_allows_auto_move
  am.set_direction(cur_dir);

  ActionCostValue auto_move_cost = 0;
  bool auto_movement_engaged = false;
  TilePtr direction_tile = map->at(CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), cur_dir));

  pair<bool, vector<string>> creature_results = creature_can_auto_move(creature);
  bool creature_move = creature_results.first;
  copy(creature_results.second.begin(), creature_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> creature_position_results = creature_position_allows_auto_move(creature, map, amf);
  bool creature_pos_move = creature_position_results.first;
  copy(creature_position_results.second.begin(), creature_position_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> tile_results = tile_allows_auto_move(creature, direction_tile, amf);
  bool tile_move = tile_results.first;

  if (!tile_results.first)
  {
    pair<bool, Direction> new_dir = get_new_direction_if_bend_in_corridor(creature, map, cur_dir);

    if (new_dir.first)
    {
      tile_move = new_dir.first;
      cur_dir = new_dir.second;
    }
  }

  copy(tile_results.second.begin(), tile_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> map_results = fov_allows_auto_move(creature, creature->get_decision_strategy()->get_fov_map());
  bool map_move = map_results.first;
  copy(map_results.second.begin(), map_results.second.end(), back_inserter(message_sids));

  Coordinate new_coord = CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), cur_dir);
  pair<bool, vector<string>> visit_results = prev_visited_coords_allow_auto_move(creature, new_coord, amf);
  bool visit_move = visit_results.first;

  if (creature_move && creature_pos_move && tile_move && map_move && visit_move)
  {
    add_coordinate_to_automove_visited(creature, new_coord, amf);
    update_turns_if_necessary(creature);
    auto_move_cost = 1;
     
    // Don't move when resting, or else the creature will attempt to
    // attack itself!
    if (d != Direction::DIRECTION_NULL)
    {
      MovementAction maction;
      auto_move_cost = maction.move(creature, cur_dir);
    }

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

      // Resting?
      if (d == Direction::DIRECTION_NULL)
      {
        IMessageManager& manager = MessageManagerFactory::instance();

        // Add another period to the "Resting......." message.
        manager.add_new_message(".");
        manager.send(MessageSpacing::NO_SPACING);
      }
    }

  }
  else
  {
    vector<string> attrs_to_remove = {CreatureProperties::CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED};

    for (auto& attr : attrs_to_remove)
    {
      creature->remove_additional_property(attr);
    }

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

// Check hunger, the turns flag, and other attributes on the creature to 
// determine if auto-move is allowed.
pair<bool, vector<string>> AutomaticMovementCoordinator::creature_can_auto_move(CreaturePtr creature)
{
  pair<bool, vector<string>> move_details;
  bool can_move = true;
  vector<string> message_sids;

  pair<bool, vector<string>> hunger_details = hunger_allows_auto_move(creature);
  copy(hunger_details.second.begin(), hunger_details.second.end(), back_inserter(message_sids));

  // No auto-movement when poisoned or in stoning!
  bool status_ok = (creature->has_status(StatusIdentifiers::STATUS_ID_POISON) == false) && (creature->has_status(StatusIdentifiers::STATUS_ID_STONE) == false);

  if (!status_ok && creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_AUTOMOVE_BAD_STATUSES));
    manager.send();
  }

  // Stop automovement if resting and HP and AP are full.
  bool rest_ok = (creature->get_automatic_movement_ref().get_direction() != Direction::DIRECTION_NULL || (creature->get_hit_points().get_full() == false || creature->get_arcana_points().get_full() == false));

  // Turns Remaining is used by timed actions, such as resting, that specify
  // that a movement (for turns, null movement) should be done for a certain
  // number of turns.
  bool turns_ok = true;
  int turns_remaining = creature->get_automatic_movement_ref().get_turns();

  // > 0 (rest, typically) ok for obvious reasons.
  // Values < 0 are used for non-counted actions (e.g., automovement)
  if (turns_remaining == 0)
  {
    turns_ok = false;
  }

  can_move = can_move && hunger_details.first && status_ok && rest_ok && turns_ok;

  move_details.first = can_move;
  move_details.second = message_sids;

  return move_details;
}

// Does the creature's position (current tile, and the surrounding ones) allow
// auto movement?
pair<bool, vector<string>> AutomaticMovementCoordinator::creature_position_allows_auto_move(CreaturePtr creature, MapPtr map, const AutomaticMovementFlags& amf)
{
  pair<bool, vector<string>> move_details = {false, {}};

  TilePtr current_tile = MapUtils::get_tile_for_creature(map, creature);
  bool items_allow_move = false;

  // Stop auto-movement when moving to a tile that has items.
  if (amf.get_ignore_items() || (current_tile && current_tile->get_items()->empty()))
  {
    items_allow_move = true;
  }

  bool feature_allows_move = false;

  // Also stop auto-movement when the tile has features present.
  if (amf.get_ignore_feature() || (current_tile && !current_tile->has_feature()))
  {
    feature_allows_move = true;
  }

  move_details.first = (items_allow_move && feature_allows_move);
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
pair<bool, vector<string>> AutomaticMovementCoordinator::tile_allows_auto_move(CreaturePtr creature, TilePtr tile, const AutomaticMovementFlags& amf)
{
  pair<bool, vector<string>> tile_details;

  tile_details.first = amf.get_ignore_tile() || (MapUtils::is_tile_available_for_creature(creature, tile));

  return tile_details;
}

// Check to see if the creature has already visited the new coordinate.
pair<bool, vector<string>> AutomaticMovementCoordinator::prev_visited_coords_allow_auto_move(CreaturePtr creature, const Coordinate& new_coord, const AutomaticMovementFlags& amf)
{
  pair<bool, vector<string>> visit_details = {amf.get_ignore_prev_visited(), {}};

  if (creature != nullptr && amf.get_ignore_prev_visited() == false)
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

  return (visit_details);
}

// Add a coordinate to the current set of coordinates visited during 
// automovement, so that the same coordinate can't be visited twice
// (no running loops!).
void AutomaticMovementCoordinator::add_coordinate_to_automove_visited(CreaturePtr creature, const Coordinate& c, const AutomaticMovementFlags& amf)
{
  if (creature != nullptr && amf.get_ignore_prev_visited() == false)
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

void AutomaticMovementCoordinator::update_turns_if_necessary(CreaturePtr creature)
{
  // If there is already a flag on the creature, decrement it
  int turns_auto = creature->get_automatic_movement_ref().get_turns();

  if (turns_auto > 0)
  {
    creature->get_automatic_movement_ref().set_turns(turns_auto - 1);
  }
}

// If the creature is moving in a corridor, and the next tile in the given
// direction is a wall, return the new direction to move in.
pair<bool, Direction> AutomaticMovementCoordinator::get_new_direction_if_bend_in_corridor(CreaturePtr creature, MapPtr map, const Direction cur_dir)
{
  pair<bool, Direction> result = {false, Direction::DIRECTION_NULL};
  vector<Coordinate> non_block_coords;
  Coordinate cur_pos;
  bool flip_dir = false;

  if (creature && map)
  {
    cur_pos = map->get_location(creature->get_id());
    vector<Coordinate> adjacent = CoordUtils::get_adjacent_map_coordinates(map->size(), cur_pos.first, cur_pos.second);

    int non_block_count = 0;

    // We're at a bend in the corridor if there are exactly two non-blocking
    // tiles adjacent to the current position.
    for (const Coordinate& cur_adj : adjacent)
    {
      TilePtr tile = map->at(cur_adj);

      if (tile && !tile->get_is_blocking(creature))
      {
        non_block_count++;
        non_block_coords.push_back(cur_adj);
      }
    }

    if (non_block_count == 2)
    {
      non_block_coords.erase(std::find(non_block_coords.begin(), non_block_coords.end(), CoordUtils::get_new_coordinate(cur_pos, DirectionUtils::get_opposite_direction(cur_dir))));
      flip_dir = true;
    }
  }

  // Translate the new coordinates back to a direction which is then returned
  // to be used to flip the automovement direction.
  if (flip_dir)
  {
    result.first = true;
    result.second = CoordUtils::get_direction(cur_pos, non_block_coords.at(0));
  }

  return result;
}