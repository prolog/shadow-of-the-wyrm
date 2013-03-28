#pragma once
#include <boost/shared_ptr.hpp>

class Display;

// Abstract animation instruction.  Subclasses will cover things like
// drawing, pausing, etc.
class AnimationInstruction
{
  public:
    virtual void execute(Display* const display) = 0; 
};

typedef boost::shared_ptr<AnimationInstruction> AnimationInstructionPtr;

