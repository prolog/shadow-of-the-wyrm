#pragma once
#include "ICryptLayoutStrategy.hpp"

class VaultCryptLayoutStrategy : public ICryptLayoutStrategy
{
  public:
    virtual void create_layout(MapPtr map, const std::tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary) override;
    virtual ~VaultCryptLayoutStrategy() = default;

  protected:
    virtual std::pair<Coordinate, Coordinate> generate_vault(MapPtr map, const std::tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary);
    virtual Coordinate get_door_location(const Direction d, const int mid_height, const int mid_width, const int vh, const int vw);
    virtual void generate_vault_entrance(MapPtr map, const int mid_height, const int mid_width, const int vault_height, const int vault_width, const Coordinate& stair_coord);
};

