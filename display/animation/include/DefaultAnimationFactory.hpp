#pragma once
#include "AnimationFactory.hpp"

class DefaultAnimationFactory : public AnimationFactory
{
  public:
    virtual AnimationInstructionPtr create_draw_instruction(const Coordinate& c, const DisplayTile& display_tile) const;
};

