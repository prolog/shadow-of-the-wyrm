#include <boost/make_shared.hpp>
#include "AStarSearchStrategy.hpp"
#include "BreadthFirstSearchStrategy.hpp"
#include "SearchStrategyFactory.hpp"
#include "UniformCostSearchStrategy.hpp"

SearchStrategyFactory::SearchStrategyFactory()
{
}

SearchStrategyFactory::~SearchStrategyFactory()
{
}

SearchStrategyPtr SearchStrategyFactory::create_search_strategy(const SearchType st, CreaturePtr creature)
{
  SearchStrategyPtr ss = boost::make_shared<AStarSearchStrategy>();
  ss->set_creature(creature);

  return ss;
}
