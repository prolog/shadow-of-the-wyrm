#pragma once
#include "AnimationInstruction.hpp"
#include "Display.hpp"

class PauseAnimationInstruction : public AnimationInstruction
{
  public:
    void execute(Display* const display) override;
};

