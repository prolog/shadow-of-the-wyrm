#include <algorithm>
#include "SearchNode.hpp"

SearchNode::SearchNode()
: location(-1,-1), depth(-1), path_cost(-1)
{
  
}

SearchNode::SearchNode(const Coordinate& c)
: location(c), depth(0), path_cost(0)
{
}

SearchNode::SearchNode(const Coordinate& c, const std::vector<Coordinate>& new_ancestors, const int new_depth, const int new_path_cost)
: location(c), ancestors(new_ancestors), depth(new_depth), path_cost(new_path_cost)
{
}

Coordinate SearchNode::get_location() const
{
  return location;
}

Coordinate SearchNode::get_parent() const
{
  Coordinate parent(-1,-1);
  
  if (!ancestors.empty())
  {
    // The parent is always the last item in the list
    parent = ancestors.at(ancestors.size() - 1);
  }
  
  return parent;
}

std::vector<Coordinate> SearchNode::get_ancestors() const
{
  return ancestors;
}

int SearchNode::get_depth() const
{
  return depth;
}

int SearchNode::get_path_cost() const
{
  return path_cost;
}

// Check to see if a coordinate has already been visited (is part of the node's ancestors),
// so that cycles can be avoided.
bool SearchNode::is_previously_visited(const Coordinate& c)
{
  // JCD FIXME DIDN'T HAVE INTERNET WHEN WRITING THIS - DOUBLE CHECK:
  return (std::find(ancestors.begin(), ancestors.end(), c) != ancestors.end());
}
