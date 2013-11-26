#pragma once
#include "DrawAnimationInstruction.hpp"

class CursesDrawAnimationInstruction : public DrawAnimationInstruction
{
  public:
    CursesDrawAnimationInstruction(const Coordinate& c, const DisplayTile& disp);

    virtual void execute(Display* const display) override;
};

