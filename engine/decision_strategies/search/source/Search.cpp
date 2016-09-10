#include "CoordUtils.hpp"
#include "CreatureTileSafetyChecker.hpp"
#include "Search.hpp"

using namespace std;

// The creature that requires the pathfinding.  The actual creature is kept so that
// it can be used for some blocking checks at the tile level.
void Search::set_creature(CreaturePtr creature)
{
  perspective_creature = creature;
}

// Try to find a path from start to end, given what can be seen in view_map.  This allows
// for imperfect knowledge, and prevents search using information that has not already
// been learned.
Coordinate Search::search(MapPtr view_map, const Coordinate& start, const Coordinate& end)
{
  Coordinate stay_put = start; // If a goal state can't be reached, stay put!
  
  set<Coordinate> visited;
  list<SearchNode> nodes = make_search_nodes(view_map, visited, start, end);

  while(true)
  {
    if (nodes.empty())
    {
      break;
    }
    
    SearchNode node = remove_front(nodes);
    visited.insert(node.get_location());

    if (goal_test(node, end))
    {
      vector<Coordinate>& ancestors = node.get_ancestors_ref();
      return ancestors[0];
    }
    
    nodes = queueing_fn(nodes, make_search_nodes(view_map, visited, end, node));
  }
  
  return stay_put;
}

bool Search::goal_test(const SearchNode& sn, const Coordinate& goal_coord)
{
  Coordinate c = sn.get_location();
  return (c == goal_coord);
}

bool Search::is_empty(const list<SearchNode>& search_queue) const
{
  return search_queue.empty();
}

SearchNode Search::remove_front(list<SearchNode>& search_queue)
{
  SearchNode front;
  
  if (!search_queue.empty())
  {
    front = search_queue.front();
    search_queue.pop_front();
  }
  
  return front;
}

list<SearchNode> Search::make_search_nodes(MapPtr view_map, set<Coordinate>& visited, const Coordinate& c, const Coordinate& goal_coordinate, SearchNode * const parent)
{
  CreatureTileSafetyChecker safety_check;
  list<SearchNode> search_nodes;

  Dimensions orig_map_dimensions = view_map->original_size();
  vector<Coordinate> coords = CoordUtils::get_adjacent_map_coordinates(orig_map_dimensions, c.first, c.second);
  
  for (const Coordinate& coord : coords)
  {
    if (visited.find(coord) != visited.end())
    {
      continue;
    }
    else
    {
      TilePtr tile = view_map->at(coord);
      
      if (tile)
      {
        // Only consider a tile for inclusion in the final path if:
        // - it isn't blocking
        // - it's safe to move there for the creature
        if (!tile->get_is_blocking(perspective_creature) &&
             safety_check.is_tile_safe_for_creature(perspective_creature, tile))
        {
          SearchNode sn(coord);
        
          int danger_cost = 0;
          FeaturePtr feature = tile->get_feature();
          if (feature != nullptr && feature->get_is_dangerous())
          {
            // If it's a dangerous feature (probably a trap), penalize the 
            // search path.
            danger_cost += 10;
          }

          int path_cost = danger_cost + 1;

          if (parent)
          {
            sn.set_location(coord);
          
            vector<Coordinate>& ancestors = parent->get_ancestors_ref();
            ancestors.push_back(parent->get_location());
            sn.set_ancestors(ancestors);
          
            // Be sure to consider the parent's path cost as well.
            path_cost += parent->get_path_cost();
          }

          // Because the queueing function considers the path cost
          // and the estimated cost to the goal, ensure that the path
          // cost is penalized for any "bad things" present on the
          // current tile.
          sn.set_path_cost(path_cost);
        
          // Used for A* search.  Use Chebyshev distance - 1 (distance from
          // next tile) plus the actual movement cost of the current tile.
          int estimated_cost = (CoordUtils::chebyshev_distance(coord, goal_coordinate) - 1) 
                             + tile->get_movement_multiplier();

          sn.set_estimated_cost_to_goal(estimated_cost);
        
          search_nodes.push_back(sn);
        }
        else
        {
          // JCD FIXME: Why aren't ghosts walking through walls?!
          // int x = 1;
        }
      }
 
      // Always set it visited, regardless.
      visited.insert(coord);
    }
  }
  
  return search_nodes;
}

// JCD FIXME refactor
list<SearchNode> Search::make_search_nodes(MapPtr view_map, set<Coordinate>& visited, const Coordinate& goal_coordinate, SearchNode& sn)
{
  Coordinate c = sn.get_location();
  return make_search_nodes(view_map, visited, c, goal_coordinate, &sn);
}
