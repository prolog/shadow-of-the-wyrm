#include "DefaultDrawAnimationInstruction.hpp"

DefaultDrawAnimationInstruction::DefaultDrawAnimationInstruction(const Coordinate& new_coords, const DisplayTile& new_tile)
: DrawAnimationInstruction(new_coords, new_tile)
{
}

void DefaultDrawAnimationInstruction::execute(Display* const display)
{
  display->draw_tile(coords.first, coords.second, tile);
}

