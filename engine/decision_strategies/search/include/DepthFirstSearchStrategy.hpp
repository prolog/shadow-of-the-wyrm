#include "Search.hpp"

class DepthFirstSearchStrategy : public Search
{
  public:
  protected:
    // Queue at start
    virtual std::list<SearchNode> queueing_fn(const std::list<SearchNode>& explored_search_nodes, const std::list<SearchNode>& new_search_nodes);
};
