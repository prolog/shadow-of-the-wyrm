#include <boost/make_shared.hpp>
#include "AnimationFactory.hpp"
#include "PauseAnimationInstruction.hpp"

AnimationInstructionPtr AnimationFactory::create_pause_instruction() const
{
  AnimationInstructionPtr pause;

  pause = boost::make_shared<PauseAnimationInstruction>();

  return pause;
}

