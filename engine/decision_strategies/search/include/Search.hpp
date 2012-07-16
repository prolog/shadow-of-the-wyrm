#pragma once
#include <list>
#include <vector>
#include <set>
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Map.hpp"
#include "SearchNode.hpp"

class Search
{
  public:
    Coordinate search(MapPtr view_map, const Coordinate& start, const Coordinate& end);
    
  protected:
    // Have we reached the end?
    bool goal_test(const SearchNode& sn, const Coordinate& end_coord);
    
    bool is_empty(const std::list<SearchNode>& search_queue) const;
    virtual SearchNode remove_front(std::list<SearchNode>& search_queue);
    
    // Create a list of search nodes given a coordinate
    std::list<SearchNode> make_search_nodes(MapPtr view_map, std::set<Coordinate>& visited, const Coordinate& c, const Coordinate& goal_coordinate, const SearchNode* const parent = NULL);
    
    // Create a list of search nodes given a search node - this will fully populate
    // depth and path cost details.
    std::list<SearchNode> make_search_nodes(MapPtr view_map, std::set<Coordinate>& visited, const Coordinate& goal_coordinate, const SearchNode& sn);
    
    // Variations on this give different search types (BFS, DFS, etc).
    virtual std::list<SearchNode> queueing_fn(const std::list<SearchNode>& explored_search_nodes, const std::list<SearchNode>& new_search_nodes) = 0;
};

typedef boost::shared_ptr<Search> SearchStrategyPtr;
