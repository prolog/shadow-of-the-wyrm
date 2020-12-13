#pragma once
#include "Command.hpp"
#include "Creature.hpp"
#include "Map.hpp"

class NPCUseEquipItemDecisionStrategy
{
  public:
    CommandPtr decide(CreaturePtr creature, MapPtr map);
    bool should_equip_weapon(CreaturePtr creature, ItemPtr item);
    bool should_equip_wearable(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation ewl = EquipmentWornLocation::EQUIPMENT_WORN_NONE);

  protected:
    virtual CommandPtr get_equip_weapon_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_equip_armour_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_equip_ring_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_equip_amulet_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_equip_ammunition_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_use_wand_decision(CreaturePtr creature, ItemPtr item, MapPtr view_map);
    virtual CommandPtr get_use_book_decision(CreaturePtr creature, ItemPtr item);

};