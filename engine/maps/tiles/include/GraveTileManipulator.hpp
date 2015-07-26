#pragma once
#include "ITileManipulator.hpp"

class GraveTileManipulator : public ITileManipulator
{
  public:
    bool dig(CreaturePtr creature, TilePtr tile) override;
};

