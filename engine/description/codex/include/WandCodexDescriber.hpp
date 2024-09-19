#pragma once
#include "CodexDescriber.hpp"
#include "Wand.hpp"

class WandCodexDescriber : public CodexDescriber
{
  public:
    WandCodexDescriber(WandPtr wand);
    virtual ~WandCodexDescriber() = default;

    std::string describe_details() const override;

  protected:
    WandPtr wand;
};

