#pragma once
#include "Creature.hpp"

class PacificationCalculator
{
  public:
    int calculate_pct_chance_pacify_music(CreaturePtr music_cr, CreaturePtr fov_cr);
};

