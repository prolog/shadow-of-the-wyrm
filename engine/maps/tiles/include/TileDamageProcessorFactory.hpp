#pragma once
#include "TileDamageProcessor.hpp"
#include "Damage.hpp"

class TileDamageProcessorFactory
{
  public:
    TileDamageProcessorPtr create_tile_damage_processor(const DamageType dt);
};

