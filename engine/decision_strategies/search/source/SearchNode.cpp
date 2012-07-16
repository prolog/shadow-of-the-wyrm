#include <algorithm>
#include <sstream>
#include <boost/foreach.hpp>
#include "SearchNode.hpp"

using namespace std;

SearchNode::SearchNode()
: location(-1,-1), path_cost(-1), estimated_cost_to_goal(0)
{
  
}

SearchNode::SearchNode(const Coordinate& c)
: location(c), path_cost(0), estimated_cost_to_goal(0)
{
}

SearchNode::SearchNode(const Coordinate& c, const vector<Coordinate>& new_ancestors, const int new_path_cost, const int new_cost_to_goal)
: location(c), ancestors(new_ancestors), path_cost(new_path_cost), estimated_cost_to_goal(new_cost_to_goal)
{
}

void SearchNode::set_location(const Coordinate& new_location)
{
  location = new_location;
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

void SearchNode::set_ancestors(const vector<Coordinate>& new_ancestors)
{
  ancestors = new_ancestors;
}

vector<Coordinate> SearchNode::get_ancestors() const
{
  return ancestors;
}

int SearchNode::get_depth() const
{
  return ancestors.size();
}

void SearchNode::set_path_cost(const int new_path_cost)
{
  path_cost = new_path_cost;
}

int SearchNode::get_path_cost() const
{
  return path_cost;
}

void SearchNode::set_estimated_cost_to_goal(const int new_estimated_cost_to_goal)
{
  estimated_cost_to_goal = new_estimated_cost_to_goal;
}

int SearchNode::get_estimated_cost_to_goal() const
{
  return estimated_cost_to_goal;
}

// Check to see if a coordinate has already been visited (is part of the node's ancestors),
// so that cycles can be avoided.
bool SearchNode::is_previously_visited(const Coordinate& c) const
{
  return (find(ancestors.begin(), ancestors.end(), c) != ancestors.end());
}

string SearchNode::str() const
{
  ostringstream ss;
  
  BOOST_FOREACH(const Coordinate& c, ancestors)
  {
    ss << "(" << c.first << "," << c.second << ") ";
  }
  
  ss << "(" << location.first << "," << location.second << ") ";
  
  return ss.str();
}
