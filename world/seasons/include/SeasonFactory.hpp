#pragma once
#include "ISeason.hpp"

class SeasonFactory
{
  public:
    static ISeasonPtr create_season(const Season season);

  protected:
    SeasonFactory();
    ~SeasonFactory();
};
