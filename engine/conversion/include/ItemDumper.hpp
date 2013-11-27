#pragma once
#include "Item.hpp"
#include "StringConverter.hpp"

class ItemDumper : public StringConverter
{
  public:
    ItemDumper(ItemPtr new_item);

    std::string str() const override;

  protected:
    ItemPtr item;
};
