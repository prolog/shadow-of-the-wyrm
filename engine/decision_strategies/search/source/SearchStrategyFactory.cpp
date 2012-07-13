#include <boost/make_shared.hpp>
#include "BreadthFirstSearchStrategy.hpp"
#include "SearchStrategyFactory.hpp"

using boost::make_shared;

SearchStrategyFactory::SearchStrategyFactory()
{
}

SearchStrategyFactory::~SearchStrategyFactory()
{
}

SearchStrategyPtr SearchStrategyFactory::create_search_strategy(const SearchType st)
{
  SearchStrategyPtr ss = make_shared<BreadthFirstSearchStrategy>();
  return ss;
}
