#include "BreadthFirstSearchStrategy.hpp"

std::list<SearchNode> BreadthFirstSearchStrategy::queueing_fn(const std::list<SearchNode>& search_nodes, const std::list<SearchNode>& new_nodes)
{
  std::list<SearchNode> queue = search_nodes;

  for (const SearchNode& s : new_nodes)
  {
    queue.push_back(s);
  }

  return queue;
}
