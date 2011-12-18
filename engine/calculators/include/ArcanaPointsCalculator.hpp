#pragma once
#include "Creature.hpp"

class ArcanaPointsCalculator
{
  public:
    static int calculate_arcana_points_bonus(const CreaturePtr& c);

  protected:
    ArcanaPointsCalculator();
    ~ArcanaPointsCalculator();
};
