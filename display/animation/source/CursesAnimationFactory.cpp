#include "CursesAnimationFactory.hpp"
#include "CursesDrawAnimationInstruction.hpp"
#include <boost/make_shared.hpp>

AnimationInstructionPtr CursesAnimationFactory::create_draw_instruction(const Coordinate& c, const DisplayTile& display_tile) const
{
  AnimationInstructionPtr draw_instruction = boost::make_shared<CursesDrawAnimationInstruction>(c, display_tile);

  return draw_instruction;
}
