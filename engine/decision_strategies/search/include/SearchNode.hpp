#pragma once
#include <vector>
#include "common.hpp"

class SearchNode
{
  public:
    SearchNode();
    SearchNode(const Coordinate& new_location);
    SearchNode(const Coordinate& new_location, const std::vector<Coordinate>& ancestors, const int new_path_cost);

    void set_location(const Coordinate& new_location);
    Coordinate get_location() const;
    
    // Calculated, so no set-fn.
    Coordinate get_parent() const;
    
    void set_ancestors(const std::vector<Coordinate>& new_ancestors);
    std::vector<Coordinate> get_ancestors() const;
    
    // Calculated
    int get_depth() const;
    
    void set_path_cost(const int new_path_cost);
    int get_path_cost() const;
    
    bool is_previously_visited(const Coordinate& c) const;

  protected:
    Coordinate location;
    std::vector<Coordinate> ancestors;
    int path_cost;
};
