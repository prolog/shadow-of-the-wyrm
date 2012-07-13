#include <boost/foreach.hpp>
#include "BreadthFirstSearchStrategy.hpp"

std::list<SearchNode> BreadthFirstSearchStrategy::queueing_fn(std::vector<SearchNode>& new_nodes)
{
  std::list<SearchNode> queue;

  BOOST_FOREACH(SearchNode s, new_nodes)
  {
    queue.push_back(s);
  }

  return queue;
}
