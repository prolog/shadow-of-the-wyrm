#include "DefaultAnimationFactory.hpp"
#include "DefaultDrawAnimationInstruction.hpp"

AnimationInstructionPtr DefaultAnimationFactory::create_draw_instruction(const Coordinate& c, const DisplayTile& display_tile) const
{
  AnimationInstructionPtr draw_instruction = std::make_shared<DefaultDrawAnimationInstruction>(c, display_tile);

  return draw_instruction;
}
