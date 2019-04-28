#pragma once
#include "IDescriber.hpp"
#include "Tile.hpp"

class TileDescriber : public IDescriber
{
  public:
    TileDescriber(CreaturePtr viewing_creature, TilePtr new_tile);

    std::string describe() const override;

  protected:
    CreaturePtr viewing_creature;
    TilePtr tile;
};
