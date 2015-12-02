#pragma once
#include "common.hpp"

class CreatureGenerationConstants
{
  public:
    static const float BASE_EXPERIENCE_LOWER_MULTIPLIER;
    static const float BASE_EXPERIENCE_UPPER_MULTIPLIER;
    static const uint MIN_CREATURES_FOR_MAP_UPDATE;
    static const int CREATURE_DROP_RATE;
    static const int HUMANOID_CURRENCY_RATE;
    static const int CREATURE_GENERATION_UNLIMITED;

  protected:
    CreatureGenerationConstants();
    ~CreatureGenerationConstants();
};

