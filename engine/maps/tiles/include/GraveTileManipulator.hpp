#pragma once
#include "ITileManipulator.hpp"

class GraveTileManipulator : public ITileManipulator
{
  public:
    bool dig(CreaturePtr creature, MapPtr map, TilePtr tile) override;
};

