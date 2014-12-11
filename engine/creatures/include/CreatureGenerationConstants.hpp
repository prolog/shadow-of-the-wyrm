#pragma once
#include "common.hpp"

class CreatureGenerationConstants
{
  public:
    static const float BASE_EXPERIENCE_LOWER_MULTIPLIER;
    static const float BASE_EXPERIENCE_UPPER_MULTIPLIER;
    static const uint MIN_CREATURES_FOR_MAP_UPDATE;

  protected:
    CreatureGenerationConstants();
    ~CreatureGenerationConstants();
};

