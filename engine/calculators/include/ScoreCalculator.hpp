#pragma once
#include "common.hpp"
#include "Creature.hpp"

// Calculate the score (for the high score list) for the player.
class ScoreCalculator
{
  public:
    ulonglong calculate_score(CreaturePtr creature);
};

