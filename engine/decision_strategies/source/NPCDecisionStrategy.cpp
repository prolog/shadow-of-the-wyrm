#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Commands.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "NPCDecisionStrategy.hpp"
#include "RNG.hpp"

using std::set;
using std::string;
using std::vector;
using boost::make_shared;

bool NPCDecisionStrategy::get_confirmation()
{
  return true;
}

// The basic decision structure for NPCs.  The individual get_decision_for functions are pure virtual within this class,
// and implemented by concrete decision strategies.
CommandPtr NPCDecisionStrategy::get_decision(const string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map)
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
    command = make_shared<SearchCommand>();
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

        if (MapUtils::are_coordinates_adjacent(c_this, c_threat))
        {
          Direction direction = MapUtils::get_direction(c_this, c_threat);
          
          // create movement command, return.
          CommandPtr command = make_shared<AttackCommand>(direction);
          return command;
        }
      }
    }
    
    // Try the next threat level.
    t_it++;
  }  
  
  return no_attack;
}

// Get the decision for where to move.
CommandPtr NPCDecisionStrategy::get_movement_decision(const string& this_creature_id)
{   
  CommandPtr movement_command;

  Game* game = Game::instance();
  
  if (game)
  {
    MapPtr current_map = game->get_current_map();
    Dimensions current_dimensions = current_map->size();
    Coordinate this_creature_coords = current_map->get_location(this_creature_id);
   
    int this_row = this_creature_coords.first;
    int this_col = this_creature_coords.second;
   
    vector<Coordinate> adjacent_coordinates = MapUtils::get_adjacent_map_coordinates(current_dimensions, this_row, this_col);
    vector<Coordinate> choice_coordinates = get_adjacent_coordinates_without_creatures(current_map, adjacent_coordinates);
    
    // Pick a tile if not empty
    if (!choice_coordinates.empty())
    {
      Coordinate movement_coord = choice_coordinates.at(RNG::range(0, choice_coordinates.size()-1));
      Direction direction = MapUtils::get_direction(this_creature_coords, movement_coord);
      movement_command = make_shared<MovementCommand>(direction);
    }
  }

  return movement_command;
}

// Get a list of the adjacent coordinates that do not contain creatures
vector<Coordinate> NPCDecisionStrategy::get_adjacent_coordinates_without_creatures(MapPtr current_map, const vector<Coordinate>& all_adjacent_coordinates)
{
  vector<Coordinate> coords_without_creatures;
  
  BOOST_FOREACH(Coordinate c, all_adjacent_coordinates)
  {
    // Don't move if there's a creature on that coordinate.
    TilePtr adjacent_tile = current_map->at(c.first, c.second);
    
    if (adjacent_tile->has_creature())
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
