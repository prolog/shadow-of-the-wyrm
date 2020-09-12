#pragma once
#include <memory>
#include "common.hpp"

class Display;

// Abstract animation instruction.  Subclasses will cover things like
// drawing, pausing, etc.
class AnimationInstruction
{
  public:
    virtual void execute(Display* const display) = 0; 
    virtual Coordinate get_coords() const = 0;
};

using AnimationInstructionPtr = std::shared_ptr<AnimationInstruction>;

