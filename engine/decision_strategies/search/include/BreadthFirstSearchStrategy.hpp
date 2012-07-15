#include "Search.hpp"

class BreadthFirstSearchStrategy : public Search
{
  public:
  protected:
    // Queue at end
    virtual std::list<SearchNode> queueing_fn(const std::list<SearchNode>& explored_search_nodes, const std::list<SearchNode>& new_search_nodes);
};
