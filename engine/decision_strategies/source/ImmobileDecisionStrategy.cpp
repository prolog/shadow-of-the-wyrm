#include <string>
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Commands.hpp"
#include "ImmobileDecisionStrategy.hpp"
#include "MapUtils.hpp"

using namespace std;
using boost::make_shared;

ImmobileDecisionStrategy::ImmobileDecisionStrategy(ControllerPtr new_controller)
: controller(new_controller)
{
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_map(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map)
{
  CommandPtr command = make_shared<SearchCommand>(); // Default action.

  // JCD FIXME: This can mostly be refactored into NPC decision strategy, later.
  if (view_map)
  {
    // Iterate through the threats in order of threatiness
    ThreatMap threat_map = threat_ratings.get_all_threats();
    ThreatMap::const_reverse_iterator t_it = threat_map.rbegin();
    
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
          Coordinate c_this   = view_map->get_location(this_creature_id);

          if (MapUtils::are_coordinates_adjacent(c_this, c_threat))
          {
            Direction direction = MapUtils::get_direction(c_this, c_threat);
            
            // create movement command, return.
            command = make_shared<AttackCommand>(direction);
            return command;
          }
        }
      }
      
      // Try the next threat level.
      t_it++;
    }
  }

  return command;
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_inventory(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr null;
  return null;
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_equipment(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr null;
  return null;
}
