#pragma once
#include <string>

class ItemProperties
{
  public:
    static const std::string ITEM_PROPERTIES_DIG_HARDNESS;
    static const std::string ITEM_PROPERTIES_DIG_BREAKAGE_PCT_CHANCE;
    static const std::string ITEM_PROPERTIES_SEED_ITEM_ID;

  protected:
    ItemProperties();
    ~ItemProperties();
};
