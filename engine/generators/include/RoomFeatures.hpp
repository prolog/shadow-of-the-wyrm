#pragma once
#include <string>

// Constants used to refer to particular room features during dungeon/etc
// generation, so that features can be tracked and not repeated when
// creating the map.
class RoomFeatures
{
  public:
    static const std::string ROOM_FEATURE_ZOO;
    static const std::string ROOM_FEATURE_ALTAR;
    static const std::string ROOM_FEATURE_TREASURE_ROOM;
    static const std::string ROOM_FEATURE_REST_ROOM;
    static const std::string ROOM_FEATURE_NODE;
    static const std::string ROOM_FEATURE_GRAVE;
    static const std::string ROOM_FEATURE_SPRING;
    static const std::string ROOM_FEATURE_CRAFT_ROOM;
    static const std::string ROOM_FEATURE_MAGIC_TREE;
    static const std::string ROOM_FEATURE_SHOP;
    static const std::string ROOM_FEATURE_BEER_HALL;
    static const std::string ROOM_FEATURE_ORCHARD;
    static const std::string ROOM_FEATURE_VEGETATION;
    static const std::string ROOM_FEATURE_LITTLE_LIBRARY;

  protected:
    RoomFeatures();
    ~RoomFeatures();
};

