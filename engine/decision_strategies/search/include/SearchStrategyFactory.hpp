#pragma once
#include "Search.hpp"
#include "SearchTypes.hpp"

class SearchStrategyFactory
{
  public:
    static SearchStrategyPtr create_search_strategy(const SearchType st);

  protected:
    SearchStrategyFactory();
    ~SearchStrategyFactory();
};
