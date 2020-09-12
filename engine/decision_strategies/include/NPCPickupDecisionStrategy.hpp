#pragma once
#include "Command.hpp"
#include "Creature.hpp"
#include "Map.hpp"

class NPCPickupDecisionStrategy
{
  public:
    CommandPtr decide(CreaturePtr creature, MapPtr map);

  protected:
    virtual CommandPtr get_pick_up_weapon_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_pick_up_armour_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_pick_up_amulet_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_pick_up_ring_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_pick_up_ammunition_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_pick_up_wand_decision(CreaturePtr creature, ItemPtr item);
    virtual CommandPtr get_pick_up_book_decision(CreaturePtr creature, ItemPtr item);

};
