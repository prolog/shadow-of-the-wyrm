#pragma once
#include "CodexDescriber.hpp"

class WearableCodexDescriber : public CodexDescriber
{
  public:
    WearableCodexDescriber(ItemPtr item);

    std::string describe_speed_bonus() const override;
};

