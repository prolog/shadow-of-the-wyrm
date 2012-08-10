#pragma once
#include "IDescriber.hpp"
#include "Tile.hpp"

class TileDescriber : public IDescriber
{
  public:
    TileDescriber(TilePtr new_tile);

    std::string describe() const;

  protected:
    TilePtr tile;
};
