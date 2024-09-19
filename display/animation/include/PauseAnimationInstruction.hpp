#pragma once
#include "AnimationInstruction.hpp"
#include "Display.hpp"

class PauseAnimationInstruction : public AnimationInstruction
{
  public:
    virtual ~PauseAnimationInstruction() = default;

    void execute(Display* const display) override;
    virtual Coordinate get_coords() const;
};

