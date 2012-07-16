#include "Search.hpp"

// I love you, A*. :)
class AStarSearchStrategy : public Search
{
  protected:
    // Queue so that the lowest cost (as measured by path cost) are at
    // the front of the queue, and thus are expanded first.
    virtual std::list<SearchNode> queueing_fn(const std::list<SearchNode>& explored_search_nodes, const std::list<SearchNode>& new_search_nodes);

    // Sort in ascending order of path cost + estimated cost to goal
    static bool path_sort_comparison(const SearchNode& sn1, const SearchNode& sn2);
};
