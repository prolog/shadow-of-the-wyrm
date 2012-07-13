#pragma once
#include <vector>
#include "common.hpp"

class SearchNode
{
  public:
    SearchNode();
    SearchNode(const Coordinate& new_location);
    SearchNode(const Coordinate& new_location, const std::vector<Coordinate>& ancestors, const int new_depth, const int new_path_cost);

    Coordinate get_location() const;
    Coordinate get_parent() const;
    std::vector<Coordinate> get_ancestors() const;
    int get_depth() const;
    int get_path_cost() const;
    bool is_previously_visited(const Coordinate& c);

  protected:
    Coordinate location;
    std::vector<Coordinate> ancestors;
    int depth;
    int path_cost;
};
