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

  protected:
    ItemProperties();
    ~ItemProperties();
};
