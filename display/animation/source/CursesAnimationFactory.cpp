#include "CursesAnimationFactory.hpp"
#include "CursesDrawAnimationInstruction.hpp"

AnimationInstructionPtr CursesAnimationFactory::create_draw_instruction(const Coordinate& c, const DisplayTile& display_tile) const
{
  AnimationInstructionPtr draw_instruction = std::make_shared<CursesDrawAnimationInstruction>(c, display_tile);

  return draw_instruction;
}
