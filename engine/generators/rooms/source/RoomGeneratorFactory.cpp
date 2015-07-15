#include "RoomGeneratorFactory.hpp"
#include "BasicRoomGenerator.hpp"
#include "NullRoomGenerator.hpp"
#include "RNG.hpp"
#include "XRoomGenerator.hpp"

using namespace std;

IRoomGeneratorPtr RoomGeneratorFactory::create_room_generator(const RoomType room_type)
{
  static_assert(RoomType::ROOM_TYPE_LAST == RoomType(2), "Unexpected value for ROOM_TYPE_LAST");

  IRoomGeneratorPtr room_gen;

  switch(room_type)
  {
    case RoomType::ROOM_TYPE_BASIC:
      room_gen = std::make_shared<BasicRoomGenerator>();
      break;
    case RoomType::ROOM_TYPE_X:
      room_gen = std::make_shared<XRoomGenerator>();
      break;
    default:
      room_gen = std::make_shared<NullRoomGenerator>();
      break;
  }

  return room_gen;
}

IRoomGeneratorPtr RoomGeneratorFactory::create_random_special_room_generator()
{
  RoomType rt = static_cast<RoomType>(RNG::range(static_cast<int>(RoomType::ROOM_TYPE_SPECIAL_FIRST), static_cast<int>(RoomType::ROOM_TYPE_SPECIAL_LAST_INC)));
  
  IRoomGeneratorPtr rg = create_room_generator(rt);
  return rg;
}

#ifdef UNIT_TESTS
#include "unit_tests/RoomGeneratorFactory_test.cpp"
#endif

