#include <boost/foreach.hpp>
#include "MapUtils.hpp"
#include "Search.hpp"

using std::list;
using std::vector;

// Try to find a path from start to end, given what can be seen in view_map.  This allows
// for imperfect knowledge, and prevents search using information that has not already
// been learned.
Coordinate Search::search(MapPtr view_map, const Coordinate& start, const Coordinate& end)
{
  Coordinate next_step;
  bool searching = true;
  
  list<SearchNode> nodes = make_search_nodes(view_map, start);
  
  while(searching)
  {
    if (nodes.empty())
    {
      break;
    }
    
//    SearchNode node = remove_front()
//    if (goal_test(node, end)) ...
//    nodes = queueing_fn(...)
  }
  
  return next_step;
}

bool Search::goal_test(const SearchNode& sn, const Coordinate& end_coord)
{
  Coordinate c = sn.get_location();
  return (c == end_coord);
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

list<SearchNode> Search::make_search_nodes(MapPtr view_map, const Coordinate& c)
{
  list<SearchNode> search_nodes;

  vector<Coordinate> coords = MapUtils::get_adjacent_map_coordinates(view_map->size(), c.first, c.second);
  
  BOOST_FOREACH(Coordinate coord, coords)
  {
    TilePtr tile = view_map->at(coord);
    
    if (tile)
    {
      SearchNode sn(coord);
      search_nodes.push_back(sn);
    }
  }
  
  return search_nodes;
}

list<SearchNode> Search::make_search_nodes(MapPtr view_map, const SearchNode& sn)
{
  Coordinate c = sn.get_location();
  return make_search_nodes(view_map, c);
}
