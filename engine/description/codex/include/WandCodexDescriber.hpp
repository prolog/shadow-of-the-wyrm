#pragma once
#include "CodexDescriber.hpp"

class WandCodexDescriber : public CodexDescriber
{
  public:
    WandCodexDescriber(ItemPtr item);

    std::string describe_details() const override;
};

