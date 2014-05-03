#pragma once
#include "ICryptLayoutStrategy.hpp"

class VaultCryptLayoutStrategy : public ICryptLayoutStrategy
{
  public:
    virtual void create_layout(MapPtr map, const std::tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary) override;

  protected:
    virtual std::pair<Coordinate, Coordinate> generate_vault(MapPtr map, const std::tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary);
    virtual void generate_vault_entrance(MapPtr map, const int mid_height, const int mid_width, const int vault_height, const int vault_width, const Coordinate& stair_coord);
    virtual void populate_vault(MapPtr map, const Coordinate& vault_topleft, const Coordinate& vault_bottomright);
};

