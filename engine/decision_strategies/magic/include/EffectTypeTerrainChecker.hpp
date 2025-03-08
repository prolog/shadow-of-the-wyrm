#pragma once
#include "Creature.hpp"

class EffectTypeTerrainChecker
{
  public:
    EffectTypeTerrainChecker();

    bool does_effect_match_terrain(CreaturePtr caster, MapPtr view_map, const EffectType effect_type) const;

  protected:
    static const int MIN_TERRAIN_COUNT_THRESHOLD;
    std::map<EffectType, TileSuperType> applicable_tst;
};

