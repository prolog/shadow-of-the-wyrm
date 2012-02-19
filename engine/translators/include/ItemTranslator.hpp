#pragma once
#include "Item.hpp"

class DisplayItem;

class ItemTranslator
{
  public:
    static DisplayItem create_display_item(const ItemPtr& item);

  protected:
    ItemTranslator();
    ~ItemTranslator();
};
