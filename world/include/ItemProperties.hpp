#pragma once
#include <string>

class ItemProperties
{
  public:
    static const std::string ITEM_PROPERTIES_ID;
    static const std::string ITEM_PROPERTIES_DIG_HARDNESS;
    static const std::string ITEM_PROPERTIES_BLANK;
    static const std::string ITEM_PROPERTIES_DIG_BREAKAGE_PCT_CHANCE;
    static const std::string ITEM_PROPERTIES_SEED_ITEM_ID;
    static const std::string ITEM_PROPERTIES_TREE_SPECIES_ID;
    static const std::string ITEM_PROPERTIES_DESTRUCTION_PCT_CHANCE;
    static const std::string ITEM_PROPERTIES_REPLACEMENT_SID;
    static const std::string ITEM_PROPERTIES_BRANDABLE;
    static const std::string ITEM_PROPERTIES_BRANDED;
    static const std::string ITEM_PROPERTIES_BRAND;
    static const std::string ITEM_PROPERTIES_LORE_CHECKED;
    static const std::string ITEM_PROPERTIES_CREATION_SKILL;
    static const std::string ITEM_PROPERTIES_MUSIC_PERFORMANCE;
    static const std::string ITEM_PROPERTIES_MUSIC_PERFORMANCE_FAILED;
    static const std::string ITEM_PROPERTIES_MUSIC_CHARM_RACES;
    static const std::string ITEM_PROPERTIES_LOCK_ID;
    static const std::string ITEM_PROPERTIES_MARK_AUTOMOVE;
    static const std::string ITEM_PROPERTIES_CONTRABAND;
    static const std::string ITEM_PROPERTIES_FLOATS;
    static const std::string ITEM_PROPERTIES_METABOLIZES_ALCOHOL;
    static const std::string ITEM_PROPERTIES_SUPPRESS_ITEM_GENERATION_ON_DESTRUCTION;
    static const std::string ITEM_PROPERTIES_REMAINS;
    static const std::string ITEM_PROPERTIES_GRAVE_TILE_TYPE;
    static const std::string ITEM_PROPERTIES_WALL_TILE_TYPE;
    static const std::string ITEM_PROPERTIES_FLOOR_TILE_TYPE;
    static const std::string ITEM_PROPERTIES_BUILD_FEATURE_CLASS_IDS;
    static const std::string ITEM_PROPERTIES_WATER_TILE_TYPE;
    static const std::string ITEM_PROPERTIES_PRISE;
    static const std::string ITEM_PROPERTIES_RANDART_NAME;
    static const std::string ITEM_PROPERTIES_PLANTABLE_FOOD;
    static const std::string ITEM_PROPERTIES_PLANTABLE_FOOD_MIN_QUANTITY;
    static const std::string ITEM_PROPERTIES_PLANTABLE_FOOD_MAX_QUANTITY;
    static const std::string ITEM_PROPERTIES_STATUS;
    static const std::string ITEM_PROPERTIES_NEXUS;
    static const std::string ITEM_PROPERTIES_LEVEL_UP_EFFECT;

  protected:
    ItemProperties();
    ~ItemProperties();
};
