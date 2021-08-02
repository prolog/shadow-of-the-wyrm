#pragma once
#include <string>

// Resource strings that display when a dungeon generates with particular
// special rooms.
class DungeonFeatureTextKeys
{
  public:
    static const std::string DUNGEON_FEATURE_ALTAR;
    static const std::string DUNGEON_FEATURE_TREASURE_ROOM;
    static const std::string DUNGEON_FEATURE_ZOO;
    static const std::string DUNGEON_FEATURE_REST_ROOM;
    static const std::string DUNGEON_FEATURE_NODE;
    static const std::string DUNGEON_FEATURE_GRAVE;
    static const std::string DUNGEON_FEATURE_TRAP_ROOM;
    static const std::string DUNGEON_FEATURE_SPRING;
    static const std::string DUNGEON_FEATURE_CRAFT_ROOM;
    static const std::string DUNGEON_FEATURE_MAGIC_TREE;
    static const std::string DUNGEON_FEATURE_SHOP;
    static const std::string DUNGEON_FEATURE_BEER_HALL;
    static const std::string DUNGEON_FEATURE_ORCHARD;
    static const std::string DUNGEON_FEATURE_VEGETATION;

  protected:
    DungeonFeatureTextKeys();
    ~DungeonFeatureTextKeys();
};

