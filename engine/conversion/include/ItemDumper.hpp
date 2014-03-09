#pragma once
#include "Creature.hpp"
#include "Item.hpp"
#include "StringConverter.hpp"

class ItemDumper : public StringConverter
{
  public:
    ItemDumper(CreaturePtr creature, ItemPtr new_item, bool show_additional_desc);

    std::string str() const override;

  protected:
    CreaturePtr creature;
    ItemPtr item;
    bool show_addl_desc;
};
