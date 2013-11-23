#include "AnimationFactory.hpp"
#include "PauseAnimationInstruction.hpp"

AnimationInstructionPtr AnimationFactory::create_pause_instruction() const
{
  AnimationInstructionPtr pause;

  pause = std::make_shared<PauseAnimationInstruction>();

  return pause;
}

