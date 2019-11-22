#pragma once
#include "DrawAnimationInstruction.hpp"

class DefaultDrawAnimationInstruction : public DrawAnimationInstruction
{
  public:
    DefaultDrawAnimationInstruction(const Coordinate& c, const DisplayTile& disp);

    virtual void execute(Display* const display) override;
};

