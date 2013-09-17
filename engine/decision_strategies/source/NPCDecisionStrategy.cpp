#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "CoordUtils.hpp"
#include "Commands.hpp"
#include "CreatureTileSafetyChecker.hpp"
#include "Game.hpp"
#include "NPCDecisionStrategy.hpp"
#include "RNG.hpp"
#include "SearchStrategyFactory.hpp"

using std::set;
using std::string;
using std::vector;

NPCDecisionStrategy::NPCDecisionStrategy(ControllerPtr new_controller)
: DecisionStrategy(new_controller)
{
}

// By default, always get/pick up/etc the maximum.
uint NPCDecisionStrategy::get_count(const uint max_count)
{
  return max_count;
}

bool NPCDecisionStrategy::get_confirmation()
{
  return true;
}

// The basic decision structure for NPCs.  The individual get_decision_for functions are pure virtual within this class,
// and implemented by concrete decision strategies.
CommandPtr NPCDecisionStrategy::get_nonmap_decision(const bool reprompt_on_cmd_not_found, const string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p)
{
  MapPtr nullmap;
  return get_decision(reprompt_on_cmd_not_found, this_creature_id, command_factory, keyboard_commands, nullmap, key_p);
}

CommandPtr NPCDecisionStrategy::get_decision(const bool reprompt_on_cmd_not_found, const string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map, int* key_p)
{
  CommandPtr command;
  
  CommandFactoryType factory_type = command_factory->get_factory_type();
  
  switch(factory_type)
  {
    case COMMAND_FACTORY_TYPE_MAP:
      command = get_decision_for_map(this_creature_id, command_factory, keyboard_commands, view_map);
      break;
    case COMMAND_FACTORY_TYPE_INVENTORY:
      command = get_decision_for_inventory(command_factory, keyboard_commands);
      break;
    case COMMAND_FACTORY_TYPE_EQUIPMENT:
      command = get_decision_for_equipment(command_factory, keyboard_commands);
      break;
    case COMMAND_FACTORY_TYPE_SELECT_TILE:
      command = get_decision_for_tile_selection(command_factory, keyboard_commands);
      break;
    default:
      break;
  }

  return command;
}

CommandPtr NPCDecisionStrategy::get_decision_for_map(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map)
{
  CommandPtr command;
  
  if (view_map)
  {
    // Attack if threatened.
    command = get_attack_decision(this_creature_id, view_map);

    // If not threatened, attempt movement.
    if (!command && can_move())
    {
      command = get_movement_decision(this_creature_id);
    }    
  }

  // If we can't move, or there are no adjacent coordinates to which the NPC can move,
  // the command will be a search command - that can always be done, and will always
  // advance to the next turn.
  if (!command)
  {
    command = boost::make_shared<SearchCommand>();
  }
  
  return command;
}

// Get the decision for what to attack.
CommandPtr NPCDecisionStrategy::get_attack_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr no_attack;

  // Iterate through the threats in order of threatiness
  ThreatMap threat_map = threat_ratings.get_all_threats();
  ThreatMap::const_reverse_iterator t_it = threat_map.rbegin();
  
  Coordinate c_this   = view_map->get_location(this_creature_id);
  TilePtr this_tile   = view_map->at(c_this);
  CreaturePtr this_cr = this_tile->get_creature();

  while (t_it != threat_map.rend())
  {
    set<string> creature_ids = t_it->second;
    
    BOOST_FOREACH(string threatening_creature_id, creature_ids)
    {
      // Check the view map to see if the creature exists
      if (view_map->has_creature(threatening_creature_id))
      {
        // Check if adjacent to this_creature_id
        Coordinate c_threat = view_map->get_location(threatening_creature_id);

        if (CoordUtils::are_coordinates_adjacent(c_this, c_threat))
        {
          Direction direction = CoordUtils::get_direction(c_this, c_threat);
          
          // create movement command, return.
          CommandPtr command = boost::make_shared<AttackCommand>(direction);
          return command;
        }
        else
        {
          if (can_move())
          {
            SearchStrategyPtr ss = SearchStrategyFactory::create_search_strategy(SEARCH_TYPE_BREADTH_FIRST, this_cr);
            Direction direction = CoordUtils::get_direction(c_this, ss->search(view_map, c_this, c_threat));

            if (direction != DIRECTION_NULL)
            {
              CommandPtr command = boost::make_shared<MovementCommand>(direction);
              return command;
            }
          }
        }
      }
    }
    
    // Try the next threat level.
    t_it++;
  }  
  
  return no_attack;
}

// Get the decision for where to move.
// Move stupidly (randomly) when no threat is present.
CommandPtr NPCDecisionStrategy::get_movement_decision(const string& this_creature_id)
{   
  CommandPtr movement_command;

  Game& game = Game::instance();
  
  MapPtr current_map = game.get_current_map();
  Dimensions current_dimensions = current_map->size();
  Coordinate this_creature_coords = current_map->get_location(this_creature_id);
  TilePtr this_creature_tile = current_map->at(this_creature_coords);
  CreaturePtr this_creature = this_creature_tile->get_creature();

  int this_row = this_creature_coords.first;
  int this_col = this_creature_coords.second;
   
  vector<Coordinate> adjacent_coordinates = CoordUtils::get_adjacent_map_coordinates(current_dimensions, this_row, this_col);
  vector<Coordinate> choice_coordinates = get_adjacent_safe_coordinates_without_creatures(current_map, adjacent_coordinates, this_creature);
    
  // Pick a tile if not empty
  if (!choice_coordinates.empty())
  {
    Coordinate movement_coord = choice_coordinates.at(RNG::range(0, choice_coordinates.size()-1));
    Direction direction = CoordUtils::get_direction(this_creature_coords, movement_coord);
    movement_command = boost::make_shared<MovementCommand>(direction);
  }

  return movement_command;
}

// Get a list of the adjacent coordinates that do not contain creatures
vector<Coordinate> NPCDecisionStrategy::get_adjacent_safe_coordinates_without_creatures(MapPtr current_map, const vector<Coordinate>& all_adjacent_coordinates, CreaturePtr this_creature)
{
  CreatureTileSafetyChecker safety_checker;
  vector<Coordinate> coords_without_creatures;
  
  BOOST_FOREACH(Coordinate c, all_adjacent_coordinates)
  {
    // Don't move if there's a creature on that coordinate.
    TilePtr adjacent_tile = current_map->at(c.first, c.second);
    
    if (adjacent_tile->has_creature() || (!safety_checker.is_tile_safe_for_creature(this_creature, adjacent_tile)))
    {
      continue;
    }
    else
    {
      coords_without_creatures.push_back(c);
    }
  }
  
  return coords_without_creatures;
}

// Most creatures can move.  Those that can't should have a different decision strategy,
// and override this function.
bool NPCDecisionStrategy::can_move() const
{
  return true;
}
