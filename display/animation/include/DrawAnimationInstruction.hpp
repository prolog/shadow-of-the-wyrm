#pragma once
#include "AnimationInstruction.hpp"
#include "Display.hpp"

// An abstract "draw" instruction.  This will need to be subclassed
// appropriately by each type of display (curses, graphical, etc).
class DrawAnimationInstruction : public AnimationInstruction
{
  public:
    DrawAnimationInstruction(const Coordinate& new_coords, const DisplayTile& disp);

    virtual void execute(Display* const display) override = 0;

  protected:
    Coordinate coords;
    DisplayTile tile;
};

