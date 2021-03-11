#pragma once
#include <string>

class ItemProperties
{
  public:
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

  protected:
    ItemProperties();
    ~ItemProperties();
};
