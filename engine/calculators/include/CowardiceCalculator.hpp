#pragma once
#include "Creature.hpp"

class CowardiceCalculator
{
  public:
    CowardiceCalculator();

    int get_pct_chance_turn_to_fight(CreaturePtr creature) const;
    int get_pct_chance_rage_fight(CreaturePtr creature) const;

  protected:
    void initialize();

    static const int BASE_PCT_CHANCE_TURN_TO_FIGHT;
    static const int BASE_PCT_CHANCE_RAGE_FIGHT;

    static std::map<CreatureSize, int> TURN_TO_FIGHT;
    static std::map<CreatureSize, int> RAGE_FIGHT;
};

