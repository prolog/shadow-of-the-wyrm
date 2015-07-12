#pragma once
#include "IRoomGenerator.hpp"
#include "RoomTypes.hpp"

class RoomGeneratorFactory
{
  public:
    IRoomGeneratorPtr create_room_generator(const RoomType room_type);
    IRoomGeneratorPtr create_random_special_room_generator();
};

