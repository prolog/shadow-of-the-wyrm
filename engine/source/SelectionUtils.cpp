#include "AttackTypes.hpp"
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "MapCursor.hpp"
#include "MapUtils.hpp"
#include "SelectionUtils.hpp"

using namespace std;

// select the nearest hostile target for the initial cursor location - this is done so that the user has to do less
// to select a target, and "nearest hostile" is a good enough heuristic, for now.
void SelectionUtils::select_nearest_hostile_target(CreaturePtr creature, MapPtr map)
{
  if (creature && map)
  {
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();

    // Sort hostile creatures by location.  Since this is a regular map, there is only one creature allowed per
    // distance - so if there are several distance-1 creatures, only one will be chosen for the map.
    std::multimap<int, pair<string, Coordinate>> hostile_creature_distance_map = MapUtils::create_distance_map(creature, fov_map, true /* hostile to creature */);

    // We may by this point have the nearest hostile creature:
    if (!hostile_creature_distance_map.empty())
    {
      pair<string, Coordinate> target_creature_details = hostile_creature_distance_map.begin()->second;
      set_target(creature, ATTACK_TYPE_RANGED, target_creature_details, map);
    }
  }
}

// Select an existing target.  Because creatures can move about after the target was previously
// acquired, update the target (if necessary) to reflect the creature's current position on the
// map.
void SelectionUtils::select_existing_target(CreaturePtr creature, MapPtr map)
{
  if (creature && map && has_target(creature, ATTACK_TYPE_RANGED))
  {
    // Set the target:
    string ranged_s = Integer::to_string(ATTACK_TYPE_RANGED);
    TargetMap& target_map = creature->get_target_map_ref();
    TargetMap::iterator t_it = target_map.find(ranged_s);
    pair<string, Coordinate>& target_details = t_it->second;
    string creature_id = target_details.first;
    
    MapCursor mc;

    if (map->has_location(creature_id))
    {
      Coordinate creature_loc = map->get_location(creature_id);
      target_details.second = creature_loc; // Ensure the location of the creature is up to date!
      mc.set_cursor_location(map, creature_loc);
    }
    else
    {
      target_map.erase(t_it);
      mc.reset_cursor(map);
    }
  }
}

// Select the previous or next target from the current target.
void SelectionUtils::select_target_in_cycle(CreaturePtr creature, MapPtr map, const SelectCreatureType sct)
{
  if (creature != nullptr)
  {
    string ranged_s = Integer::to_string(ATTACK_TYPE_RANGED);
    TargetMap& target_map = creature->get_target_map_ref();
    TargetMap::iterator t_it = target_map.find(ranged_s);
    pair<string, Coordinate>& target_details = t_it->second;
    string target_creature_id = target_details.first;

    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();

    std::multimap<int, pair<string, Coordinate>> distance_map = MapUtils::create_distance_map(creature, fov_map, false /* not hostile to creature */);

    // Iterate through the distance map, updating the previous and next values.
    // Once we reach the current target, figure out what to target next, and
    // do so.
    size_t dist_size = distance_map.size();
    if (dist_size >= 1)
    {
      pair<string, Coordinate> prev, next;

      // Size 1: Prev/next are the same element.
      if (dist_size == 1)
      {
        prev = next = distance_map.begin()->second;

        set_target(creature, ATTACK_TYPE_RANGED, prev, fov_map);
      }
      else // size must be >= 2
      {
        // If the first element is a match, "prev" is the last item.
        prev = distance_map.rbegin()->second;
        next = distance_map.begin()++->second;
        for (std::multimap<int, pair<string, Coordinate>>::iterator dist_pair = distance_map.begin(); dist_pair != distance_map.end(); dist_pair++)
        {
          string cur_target_creature_id = dist_pair->second.first;

          // We've found a match in the creature map!
          // Set the target based on whether we want the next/prev.
          if (cur_target_creature_id == target_creature_id)
          {
            if (sct == SELECT_CREATURE_NEXT)
            {
              set_target(creature, ATTACK_TYPE_RANGED, next, fov_map);
            }
            else
            {
              set_target(creature, ATTACK_TYPE_RANGED, prev, fov_map);
            }
          }

          auto potential_next = dist_pair++;
          if (potential_next != distance_map.end())
          {
            next = potential_next->second;
          }
          else // end of the map - use the beginning
          {
            next = distance_map.begin()->second;
          }

          // Once the incrementing is done, "prev" will be the element that
          // we currently have now.
          prev = dist_pair->second;
        }
      }
    }
  }
}

// Does the creature have a target defined for a particular attack type?
bool SelectionUtils::has_target(CreaturePtr creature, const AttackType attack_type)
{
  bool has_target = false;

  if (creature)
  {
    TargetMap tmap = creature->get_target_map();
    return (tmap.find(Integer::to_string(attack_type)) != tmap.end());
  }

  return has_target;
}

// Set targetting/selection information.
void SelectionUtils::set_target(CreaturePtr creature, const AttackType attack_type, const std::pair<std::string, Coordinate>& target_pair, MapPtr map)
{
  Coordinate target_coordinates = target_pair.second;

  // Set it in the targetting map attached to the creature:
  TargetMap& target_map = creature->get_target_map_ref();
  target_map[Integer::to_string(ATTACK_TYPE_RANGED)] = target_pair;

  // Set it on the actual map:
  MapCursor mc;
  mc.set_cursor_location(map, target_coordinates);
}
