#include <boost/make_shared.hpp>
#include "BreadthFirstSearchStrategy.hpp"
#include "DepthFirstSearchStrategy.hpp"
#include "SearchStrategyFactory.hpp"
#include "UniformCostSearchStrategy.hpp"

using boost::make_shared;

SearchStrategyFactory::SearchStrategyFactory()
{
}

SearchStrategyFactory::~SearchStrategyFactory()
{
}

SearchStrategyPtr SearchStrategyFactory::create_search_strategy(const SearchType st)
{
  SearchStrategyPtr ss = make_shared<DepthFirstSearchStrategy>();
  return ss;
}
