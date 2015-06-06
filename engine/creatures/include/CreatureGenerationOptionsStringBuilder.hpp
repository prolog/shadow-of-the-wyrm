#pragma once
#include "CreatureGenerationOptions.hpp"

class CreatureGenerationOptionsStringBuilder
{
  public:
    std::string build(const CreatureGenerationOptions& cgo);
};

