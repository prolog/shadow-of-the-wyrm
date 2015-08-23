#pragma once
#include <string>

class ItemProperties
{
  public:
    static const std::string ITEM_PROPERTIES_DIG_HARDNESS;
    static const std::string ITEM_PROPERTIES_DIG_BREAKAGE_PCT_CHANCE;

  protected:
    ItemProperties();
    ~ItemProperties();
};
