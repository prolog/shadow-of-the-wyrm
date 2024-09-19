#pragma once
#include "IDescriber.hpp"
#include "Tile.hpp"

class TileDescriber : public IDescriber
{
  public:
    TileDescriber(CreaturePtr viewing_creature, TilePtr new_tile, const bool is_world_map);
    virtual ~TileDescriber() = default;

    std::string describe() const override;

  protected:
    CreaturePtr viewing_creature;
    TilePtr tile;
    bool is_world_map;
};
