#pragma once
#include "CodexDescriber.hpp"
#include "Consumable.hpp"

class ConsumableCodexDescriber : public CodexDescriber
{
  public: 
    ConsumableCodexDescriber(ConsumablePtr consumable);
    virtual ~ConsumableCodexDescriber() = default;

    std::string describe_for_synopsis_line() const override;
    std::string describe_details() const override;

  protected:
    ConsumablePtr consumable;
};

