#pragma once
#include <memory>

class Display;

// Abstract animation instruction.  Subclasses will cover things like
// drawing, pausing, etc.
class AnimationInstruction
{
  public:
    virtual void execute(Display* const display) = 0; 
};

using AnimationInstructionPtr = std::shared_ptr<AnimationInstruction>;

