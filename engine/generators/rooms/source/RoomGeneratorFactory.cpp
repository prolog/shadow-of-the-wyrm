#include "RoomGeneratorFactory.hpp"
#include "BasicRoomGenerator.hpp"
#include "CaveInRoomGenerator.hpp"
#include "DankRoomGenerator.hpp"
#include "MushRoomGenerator.hpp"
#include "NullRoomGenerator.hpp"
#include "RNG.hpp"
#include "WetRoomGenerator.hpp"
#include "XRoomGenerator.hpp"

using namespace std;

IRoomGeneratorPtr RoomGeneratorFactory::create_room_generator(const RoomType room_type)
{
  static_assert(RoomType::ROOM_TYPE_LAST == RoomType(6), "Unexpected value for ROOM_TYPE_LAST");

  IRoomGeneratorPtr room_gen;

  switch(room_type)
  {
    case RoomType::ROOM_TYPE_BASIC:
      room_gen = std::make_unique<BasicRoomGenerator>();
      break;
    case RoomType::ROOM_TYPE_X:
      room_gen = std::make_unique<XRoomGenerator>();
      break;
    case RoomType::ROOM_TYPE_WET:
      room_gen = std::make_unique<WetRoomGenerator>();
      break;
    case RoomType::ROOM_TYPE_DANK:
      room_gen = std::make_unique<DankRoomGenerator>();
      break;
    case RoomType::ROOM_TYPE_CAVE_IN:
      room_gen = std::make_unique<CaveInRoomGenerator>();
      break;
    case RoomType::ROOM_TYPE_MUSH_ROOM:
      room_gen = std::make_unique<MushRoomGenerator>();
      break;
    default:
      room_gen = std::make_unique<NullRoomGenerator>();
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

