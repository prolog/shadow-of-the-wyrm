#pragma once
#include "DeathManager.hpp"

class CreatureDeathManager : public DeathManager
{
  public:
    CreatureDeathManager(CreaturePtr attacking_creature, CreaturePtr dead_creature, MapPtr current_map);
    virtual ~CreatureDeathManager();
    
    void die() const override;

  protected:
    void add_creature_death_messages(CreaturePtr attacking_creature, CreaturePtr dead_creature) const;
    void remove_quests_from_player(MapPtr map, CreaturePtr dead_creature) const;
    void remove_creature_equipment_and_drop_inventory_on_tile(MapPtr map, CreaturePtr dead_creature, IInventoryPtr ground) const;
    void potentially_generate_random_drop(CreaturePtr attacking_creature, CreaturePtr dead_creature, IInventoryPtr ground) const;
    void potentially_generate_corpse(CreaturePtr attacking_creature, CreaturePtr dead_creature, IInventoryPtr ground) const;
    void potentially_generate_primordial_essence(CreaturePtr attacking_creature, CreaturePtr dead_creature, IInventoryPtr ground) const;
};

