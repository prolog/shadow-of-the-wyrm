#pragma once
#include "CodexDescriber.hpp"
#include "Wand.hpp"

class WandCodexDescriber : public CodexDescriber
{
  public:
    WandCodexDescriber(WandPtr wand);

    std::string describe_details() const override;

  protected:
    WandPtr wand;
};

