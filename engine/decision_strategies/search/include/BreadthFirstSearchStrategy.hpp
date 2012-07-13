#include "Search.hpp"

class BreadthFirstSearchStrategy : public Search
{
  public:
  protected:
    // Queue at end
    virtual std::list<SearchNode> queueing_fn(std::vector<SearchNode>& search_nodes);
};
