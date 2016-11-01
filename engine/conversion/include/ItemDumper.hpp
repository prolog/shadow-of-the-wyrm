#pragma once
#include "Creature.hpp"
#include "Item.hpp"
#include "StringConverter.hpp"

class ItemDumper : public StringConverter
{
  public:
    ItemDumper(CreaturePtr creature, ItemPtr new_item, bool show_additional_desc);

    std::string str() const override;
    
    void set_ignore_blindness_checks(const bool new_checks);
    bool get_ignore_blindness_checks() const;

  protected:
    CreaturePtr creature;
    ItemPtr item;
    bool show_addl_desc;
    bool ignore_blindness_checks;
};
