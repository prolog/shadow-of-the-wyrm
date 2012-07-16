#include <boost/foreach.hpp>
#include "DepthFirstSearchStrategy.hpp"

std::list<SearchNode> DepthFirstSearchStrategy::queueing_fn(const std::list<SearchNode>& search_nodes, const std::list<SearchNode>& new_nodes)
{
  // DFS queues new nodes at the start, so that they are expanded first.
  std::list<SearchNode> queue = new_nodes;

  BOOST_FOREACH(SearchNode s, search_nodes)
  {
    queue.push_back(s);
  }

  return queue;
}
