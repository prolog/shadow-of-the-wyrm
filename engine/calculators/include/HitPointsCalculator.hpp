#pragma once
#include "Creature.hpp"

class HitPointsCalculator
{
  public:
    static int calculate_hit_points_bonus(const CreaturePtr& creature);

  protected:
    HitPointsCalculator();
    ~HitPointsCalculator();
};
