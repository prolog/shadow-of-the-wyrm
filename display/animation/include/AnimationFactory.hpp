#pragma once
#include <memory>
#include "AnimationInstruction.hpp"
#include "common.hpp"
#include "Colours.hpp"
#include "DisplayTile.hpp"

// Abstract class used to create animation instructions particular to a
// certain display method (curses, graphical, etc).
class AnimationFactory
{
  public:
    virtual AnimationInstructionPtr create_draw_instruction(const Coordinate& c, const DisplayTile& display_tile) const = 0;
    virtual AnimationInstructionPtr create_pause_instruction() const;
};

using AnimationFactoryPtr = std::shared_ptr<AnimationFactory>;

