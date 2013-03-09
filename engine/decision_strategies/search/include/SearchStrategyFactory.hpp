#pragma once
#include "Creature.hpp"
#include "Search.hpp"
#include "SearchTypes.hpp"

class SearchStrategyFactory
{
  public:
    static SearchStrategyPtr create_search_strategy(const SearchType st, CreaturePtr perspective_creature);

  protected:
    SearchStrategyFactory();
    ~SearchStrategyFactory();
};
