#pragma once
#include "WearableCodexDescriber.hpp"
#include "Wearable.hpp"

class ArmourCodexDescriber : public WearableCodexDescriber
{
  public:
    ArmourCodexDescriber(WearablePtr wearable);
    virtual ~ArmourCodexDescriber() = default;
};

