#pragma once
#include "ICryptLayoutStrategy.hpp"

class EmptyCryptLayoutStrategy : public ICryptLayoutStrategy
{
  public:
    virtual void create_layout(MapPtr map, const std::tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary) override;
};

