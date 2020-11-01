#pragma once
#include "Creature.hpp"

class CreatureCalculator
{
  public:
    static void update_calculated_values(const CreaturePtr& c);
    static int get_combat_assist_pct(CreaturePtr c);
    static int get_pct_chance_pack(CreaturePtr c);

  protected:
    static const int BASE_PCT_CHANCE_PACK;
};
