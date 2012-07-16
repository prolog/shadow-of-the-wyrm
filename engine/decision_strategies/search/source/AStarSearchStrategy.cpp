#include <algorithm>
#include <boost/foreach.hpp>
#include "AStarSearchStrategy.hpp"

using namespace std;

list<SearchNode> AStarSearchStrategy::queueing_fn(const list<SearchNode>& search_nodes, const list<SearchNode>& new_nodes)
{
  list<SearchNode> queue = search_nodes;

  BOOST_FOREACH(SearchNode s, new_nodes)
  {
    queue.push_back(s);
  }

  // Since uniform cost search always expands the lowest cost nodes first,
  // sort in ascending order of path cost:
  queue.sort(AStarSearchStrategy::path_sort_comparison);

  return queue;
}

bool AStarSearchStrategy::path_sort_comparison(const SearchNode& sn1, const SearchNode& sn2)
{
  return ((sn1.get_path_cost() + sn1.get_estimated_cost_to_goal()) < (sn2.get_path_cost() + sn2.get_estimated_cost_to_goal()));
}
