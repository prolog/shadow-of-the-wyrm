#pragma once
#include "common.hpp"
#include "Creature.hpp"

// Calculate the score (for the high score list) for the player.
class ScoreCalculator
{
  public:
    ulonglong calculate_score(CreaturePtr creature);

  protected:
    void update_score_end_boss(CreaturePtr creature, ulonglong& score);
    void update_score_currency(CreaturePtr creature, ulonglong& score);
    void update_score_experience(CreaturePtr creature, ulonglong& score);
    void update_score_level(CreaturePtr creature, ulonglong& score);
    void update_score_artifacts(CreaturePtr creature, ulonglong& score);
    void update_score_spells(CreaturePtr creature, ulonglong& score);
    void update_score_conducts(CreaturePtr creature, ulonglong& score);
};

