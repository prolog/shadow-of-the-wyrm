#include <algorithm>
#include <boost/foreach.hpp>
#include "UniformCostSearchStrategy.hpp"

using std::sort;

std::list<SearchNode> UniformCostSearchStrategy::queueing_fn(const std::list<SearchNode>& search_nodes, const std::list<SearchNode>& new_nodes)
{
  std::list<SearchNode> queue = search_nodes;

  BOOST_FOREACH(SearchNode s, new_nodes)
  {
    queue.push_back(s);
  }

  // Since uniform cost search always expands the lowest cost nodes first,
  // sort in ascending order of path cost:
  queue.sort(UniformCostSearchStrategy::path_sort_comparison);

  return queue;
}

bool UniformCostSearchStrategy::path_sort_comparison(const SearchNode& sn1, const SearchNode& sn2)
{
  return (sn1.get_path_cost() < sn2.get_path_cost());
}
